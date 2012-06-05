#include "test.h"
#include "HD44780.h"

//Global variable initialisation
u16 tList[12][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
			 {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
u8 tIN[3]={0,0,0};
u8 tOUT[3]={0,0,0};
u8 tC[3]={0,0,0};
u8 tN[8]={0,0,0,0,0,0,0,0}; 
u8 nC=0;
u8 node;
u8 testCMP=0;
u8 diff;
char unit;
char pins[3]={0,0,0};
BYTE RecvdByte;
u16 temp;
type pPartSS,PartSS;
u16 ptList[12][3];

void initT()
{
	u8 i,j;
	for(i=0;i<3;i++)
	{
		tIN[i]=0;
		tOUT[i]=0;
		tC[i]=0;
	}
	for(i=0;i<8;i++)tN[i]=0;
}

//Test function...does the testing
u8 testPart()
{
	u8 i;
	PartSS=0;
	diff=0;
	pins[0]='X';
	pins[1]='X';
	pins[2]='X';
	//returns the number of conducting directions between all 3 pins
	nC=testConduct(&diff);	//and fills up the list
	if(terminalF)
	{	
		puts_cdc("\n\n");
		tListPrint();
	}
	if(procF)
	{
		for(i=0;i<12;i++)
		{
			ptList[i][0]=tList[i][0];
			ptList[i][1]=tList[i][1];
			ptList[i][2]=tList[i][2];

		}
	}
	PartSS=getPartSS(diff);	//gets the ID of the part that is most probable
	if(terminalF)
	{
		puts_cdc("\nPartSS: ");
		putINT_cdc(PartSS);
	}
	else pPartSS=PartSS;
	//terminalF=0;
	//switches depending on the PartSS value, here is where all the part specific functions all called
	switchPart(PartSS);
	
	if(PartSS)return 1;
	return 0;	
}
//Checks conductivity through form [A]->[B] while keeping the 3rd pin at the test state birefly before the test.
//5V--[680]-Vt-[A]-->[B]---GND, if Vt < 93% VCC it is conducting
//returns the Value of Vt
//the test is made just after the 3rd pin is charged to test State, and then made HiZ
//this is done so that FET devices can have their Gates still charged, while it makes no diff to other parts
//Triacs, and SCRs are an exception, here the short trigering of the gate will make a differense, but it is different to the Fets... 
u16 checkConduct(u8 A, u8 B,u8 state)
{	
	
	u8 i=TST_DEL,C; //Calculate the leftover pin
	u16 Value;
	C=3-(A+B);
	R_680(C,state); //charges the leftover pin to test State
	Delay_MS(10); //wait for charge
	quickADCsetup(B);	//sets up the ADC for a later reading
	R_680(B,LOW);
	R_0(A,HIGH);		//coneects the A pin to 5V throgh 680R 5V--[680]--[A]
	HiZ(C); 			//brings the leftover pin to HiZ
	while(i--);		
	ADCON0|=0b10; //GO/!DONE=1	//starts the ADC acq
	while(ADCON0&0b10);			//this is done just after the left over pin is HiZ
	Value = 1023-ADRES;
	R_0(A,LOW);
	Delay_MS(10);
	R_0(B,LOW);	
	Delay_MS(10);			
	HiZ(A);
	HiZ(B);
	
	if(Value < CP_HIGH ) return Value+1;	//If the read value is less the 93%of VCc then it is a conductor
	return 0;							//otherwise its not conducting
}

//runs twice through all 6 posile conductive paths between 3pins
//once while keeping the 3rd pin LOW briefly befor the test
//second while HIGH, the pin is at HiZ during the test
//returns the number of conductive paths...
//if the they don't change in both passes it returs the number for the first pass, diff=0
//if the do change, returns diff and the full uber of conductive paths...
//also diff contains the information on the nC for the first pass. diff = nC+1
u8 testConduct(u8 *diff)
{		
	
	u8 tempC=0;
	u16 Value=0;
	signed short int i=0,j=0,k=0;
	u8 number_of_conductors =0;
	initT();
	*diff = 0;
	for(k=0;k<2;k++)	//k is used for the 3rd pin state (0for LOW, 1 for High)
	{
		//loop that coveres [0]->[1],[0]->[2], [1]->2]
		for(i=0;i<2;i++)			
			for(j=i+1;j<3;j++)
				if(Value=checkConduct(i,j,k))
				{
					tList[number_of_conductors][0]=i;
					tList[number_of_conductors][1]=j;
					tList[number_of_conductors++][2]=Value;
					tIN[i]=tIN[i]+1;
					tOUT[j]=tOUT[j]+1;
					tC[i]=tC[i]+1;
					tC[j]=tC[j]+1;
				}
		//loop that coveres [2]->[1],[2]->[0], [1]->0]
		for(i=2;i>0;i--)
			for(j=i-1;j>=0;j--)
				if(Value=checkConduct(i,j,k))
				{
					tList[number_of_conductors][0]=i;
					tList[number_of_conductors][1]=j;
					tList[number_of_conductors++][2]=Value;
					tIN[i]=tIN[i]+1;
					tOUT[j]=tOUT[j]+1;
					tC[i]=tC[i]+1;
					tC[j]=tC[j]+1;
				}
				if(!k)tempC = number_of_conductors;	//keeps the nc of the first pass
	}
	
	if(number_of_conductors==0)return 0;	//if no CPs return 0, and exit function
	if(number_of_conductors == (tempC*2))	//if the Nc for both passes is the same(not 0) do furnter checking
		for(i=0;i<tempC;i++)
		{
			if((tList[i][0]!=tList[i+tempC][0])||(tList[i][1]!=tList[i+tempC][1]))//goes through the listand checks if any CP is different betwwen the passes
			{
				for(i=1;i<9;i++)
					for(j=0;j<3;j++)
						if(tC[j]==i)tN[i-1]=tN[i-1]+1;
				*diff=tempC+1;					//if it finds at list one =>diff=*diff=tempC+1 
				return number_of_conductors;	//nC = full nuber of CPs
			}
			else
			{
				for(i=0;i<3;i++)
				{
					tIN[i]/=2;
					tOUT[i]/=2;
					tC[i]/=2;
				}
				for(i=1;i<9;i++)
					for(j=0;j<3;j++)
						if(tC[j]==i)tN[i-1]=tN[i-1]+1;				
				return tempC;					//if it doesn't find any diffrence from the two passes
			}
		}										//diff remains 0, and onli the nC of the first pass is returned 
	else						//if the nuber od CPs in the different passes is different
	{
		for(i=1;i<9;i++)
			for(j=0;j<3;j++)
				if(tC[j]==i)tN[i-1]=tN[i-1]+1;
		*diff = tempC+1;								
		return number_of_conductors;
	}
}

//called only if nC =0, so no CP were found in the r680 test...
u8 testCAP_RES()
{
	u8 i,j;
	u16 vT1=0,vT2,k2;
	for(i=0;i<2;i++)
		for(j=i+1;j<3;j++)
		{	
			k2=400;
			quickADCsetup(i);
			R_0(j,LOW);
			R_470K(i,HIGH);
			while(k2--);
			ADCON0|=0b10; //GO/!DONE=1	//starts the ADC acq
			while(ADCON0&0b10);			//this is done just after the left over pin is HiZ
			vT1 = ADRES;			
			Delay_MS(10);
			ADCON0|=0b10; //GO/!DONE=1	//starts the ADC acq
			while(ADCON0&0b10);			//this is done just after the left over pin is HiZ
			vT2 = ADRES;			
			R_680(i,LOW);
			Delay_MS(10);
			R_0(i,LOW);
			HiZ(i);
			HiZ(j);			
			if(vT1>CP_HIGH) continue;
			else
			{
				tList[0][0]=i;
				tList[0][1]=j;
				tList[0][2]=1023;
				tList[1][0]=j;
				tList[1][1]=i;
				tList[1][2]=1023;
				nC=2;
				if(vT2>(vT1+CAP_DIFF)) return CAP;
				else return RES;
			}			
		}
	return ERROR5;
}


///Returns the code for the tested part, to be used with the switch function...
///1:N-JFET,2:P-JFET,3:N-MOS.4:P-MOS.5:PNP/DD-CC,6:NPN/DD-CA,7:Diode,8:Triac,9:SCR
///Error means it hasn't found any of the above, Res, Caps,DD,Zd need to be checked independantly...
type getPartSS(u8 diff)
{	
	u8 j,i,A,C,G;
	u16 test;
	u8 nN=0,nD=0;

	if(tN[1]==1)
		for(i=0;i<3;i++)
			if(tC[i]==2)
			{
				if(tIN[i]==2)
				{
					nN=1;
					nD=1;
					node=i;
					break;
				}
				if(tOUT[i]==2)
				{
					nN=1;
					node=i;
					nD=2;
					break;
				}
				nD=0;				
			}
	if((tN[1]==2)&&(nC==2))nN=2;
	if(diff)	//diff present in the HighZ 3rd pin test
	{			//must be FET
		if(nC>5)
		{
			if((tN[5]==0))
			{
			if(tN[4]==2)
			{
				for(j=0;j<3;j++)
				{
					if(tC[j]==2)node=j;					
				}
			}
			else return ERROR1;
			}
			if(tN[5]==1)
			{
				for(j=0;j<3;j++)
				{
					if(tC[j]==6)node=j;
				}
			}
			else
			{
				for(j=0;j<3;j++)
				{
					if(tC[j]!=6)node=j;
				}
			}
			return TRIAC; //Triac
		}
		if(nC==2)
		{	
			if((diff-1)==0)return NFET;	//JFET has 2 conducts, high low transition is 0-N-JFET
			else return PFET;		//is more then 0 P-JFET
		}
		if(nC==3)
		{
			if((diff-1)==1)
			{
				for(i=1;i<3;i++)
					if(tList[0][1]!=tList[i][1]) return NMOS;//N-MOS if different it's NMOS				
				return SCR;//if all the second nodes off all 3 conduct are the same its a SCR
			}
			if((diff-1)==2)return PMOS;//P-MOS
		}
		return ERROR2;			//untested...uncertain..error
	}
	if(nC==0)return testCAP_RES();
	if(nC==1)return DIODE;		//one conducts with no Diff must be Diode
	if((nC==4)&&(nN==1))
	{
			if(nD==1)return NFET;
			if(nD==2)return PFET;
	}
	if(nC!=2)return ERROR3;		//no posibiliteis other the 2 conducts..error if other then
	if(nN==2)return getPartSS2();		//2 concucts, 2 nodes, no diff are Res/antiP_D/Zener/Cap
	if(nN!=1)return ERROR4;		//only 1 node combinatons left..error if other then
	if(nD==1)					//2conducts, 1 node, direction 1(OUT), nust be NPN/DD-CA
	{
		R_680(tList[0][0],HIGH);//B
		R_0(tList[1][1],LOW);	//E
		R_680(tList[0][1],HIGH);	//C
		test=ReadADC(tList[0][1]);
		if(test<CP_HIGH)
		{
			HiZ3(tList[0][0],tList[0][1],tList[1][1]);
			return NPN; //if VCE<5V then NPN
		}
		else 
		{
			HiZ3(tList[0][0],tList[0][1],tList[1][1]);
			return CA;
		}							//else ist a double diode with CA
	}
	if(nD==2)				//2conducts, 1 node. directon 2 (IN), muct be PNP/DD-CC
	{	
		R_680(tList[0][1],LOW);//B
		R_0(tList[0][0],HIGH);	//E
		R_680(tList[1][0],LOW);	//C
		test=ReadADC(tList[1][0]);
		
		if(test>CP_LOW)
		{
			HiZ3(tList[0][0],tList[1][0],tList[0][1]);
			return PNP; //if VCE>0V then PNP
		}	
		else 
		{
			HiZ3(tList[0][0],tList[1][0],tList[0][1]);
			return CC;
		}							//else ist a double diode with CA
	}
	return NOID;				//no other posibility...error
}

//we know nC==2,nN=2,diff=0,  => bidirectional conduction between only 2 points
//tList[0][0] and tList[0][1];
type getPartSS2()
{
	u32 temp;
	u16 v1,v2,v3,v4;
	u8 tp1=tList[0][0],tp2=tList[0][1]; //loading the pin numbers
	
	quickADCsetup(tp1);					//seting the quck ADC for tp1
	R_0(tp2,LOW);						//bringing tp2 to GND ( -ADC-tp1-?-tp2---GND)
	R_470K(tp1,HIGH);					//bringing the 470K resistor to HIGH and conectiong it to tp1
										//5V--[470k]--ADC--[tp1]-?-[tp2]---GND				
	Delay_MS(10);						//debuging there should be no delay...

	//Getting 2 consecutive reading on the same part...if they change must be a cap...
	ADCON0|=0b10; //GO/!DONE=1			//get first reading on 470K
	while(ADCON0&0b10);		
	v1=ADRES;							
	Delay_MS(10);	
	ADCON0|=0b10; //GO/!DONE=1	//get second reading on 470K
	while(ADCON0&0b10);
	v2=ADRES;
	if(v2>(v1+CAP_DIFF))		//if the difference is largerer then noise then its a cap
	{
		HiZ(tp1);
		HiZ(tp2);
		return CAP;  //voltage increase over time => CAP
	}
	R_680(tp1,LOW);				//discharge if anything..
	Delay_MS(20);
	R_680(tp1,HIGH);			//connect to 680 series resitor
	ADCON0|=0b10; //GO/!DONE=1	//get first reading on 680
	while(ADCON0&0b10);
	v3=ADRES;
	Delay_MS(10);
	ADCON0|=0b10; //GO/!DONE=1	//get second reading on 680
	while(ADCON0&0b10);
	v4=ADRES;
	quickADCsetup(tp2);	//changing the ADC to tp2
	R_680(tp1,LOW);		//conecting tp1 to low saffly
	Delay_MS(20);
	R_0(tp1,LOW);		//direct conect to low		
	R_680(tp2,HIGH);	//conecting tp2 to high through 680R
	//GND--[tp1] [tp2]--ADC--[680]--5V
	ADCON0|=0b10; //GO/!DONE=1	//get second reading on 680
	while(ADCON0&0b10);
	v1=ADRES;
	HiZ(tp1);
	HiZ(tp2);
	if(v4>(v3+CAP_DIFF))return CAP;		//if the difference is larger then noise then its a CAP
	if(v4>(v1+ZENER_DD))return ZENER;	//if there is a diff larger then spec its a zenner
	if(v1>(v4+ZENER_DD))return ZENER;
	temp=v4*100;
	temp=temp/v2;	
	if(temp>RES_DD)return RES;			//if there is a difference between the 680 and the 470k series resitorm then its a RESistor
	
	return DD;									//if the values are close enoguh its a anti parallel diode..
}

u8 switchPart(type SS)
{
	double C;
	//u16 temp;
	LCD_Clear();
	LCD_CursorPosition(0);

	switch (SS)
	{
	case NFET:		
		if(temp=testNFET())
		{	
			LCD_WriteString("N-JFET rON:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case PFET:
		if(temp=testPFET())
		{	
			LCD_WriteString("P-JFET rON:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case NMOS:
		if(temp=testNMOS())
		{	
			LCD_WriteString("NMOS   rON:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case PMOS:
		if(temp=testPMOS())
		{	
			LCD_WriteString("PMOS   rON:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case NPN:
		if(temp=testNPN())		
		{	
			LCD_WriteString("NPN    hFE:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case CA:	
		if(temp=testCA())
		{	
			LCD_WriteString("CA      Vd:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case PNP:
		if(temp=testPNP())
		{	
			LCD_WriteString("PNP    hFE:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case CC:
		if(temp=testCC())	
		{	
			LCD_WriteString("CC      Vd:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case DIODE:
		if(temp=testDIODE())		
		{	
			LCD_WriteString("DIODE   Vd:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case TRIAC:
		if(temp=testTRIAC())		
		{	
			LCD_WriteString("TRIAC      ");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case SCR:
		if(temp=testSCR())		
		{	
			LCD_WriteString("SCR     vG:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case CAP:
		if(temp=testCAP())
		{	
			LCD_WriteString("Capacitor: ");
			LCD_WriteINT(temp);
			LCD_WriteChar(unit);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case RES:
		if(temp=testRES())
		{	
			LCD_WriteString("Resistance: ");
			LCD_WriteINT(temp);
			LCD_WriteChar(unit);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
		else return ERROR;
	case ZENER:
		if(temp=testZENER())
		{	
			LCD_WriteString("ZENER   Vz:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
	case DD:
		if(temp=testDD())
		{	
			LCD_WriteString("DD      Vd:");
			LCD_WriteINT(temp);
			LCD_CursorPosition(21);
			LCD_WritePinout();
			return 1;
		}
	default:
		LCD_WriteString("Error");
		return ERROR;
	}
}
//Test N-JFET, returns the Ron for 5V Vgs, and 5V--[680]-[D][S]--GND
//Pinonut for D and S is unindentifiable...sso both DS and SD will work
u16 testNFET()
{
	u8 D,S,G;
	G=node;
	if(G)D=0;
	else D=2;
	S=3-(G+D);
	pins[G]='G';
	pins[D]='D';
	pins[S]='S';
	return 1;
}
u16 testPFET()
{
	u8 D,S,G;
	G=node;
	if(G)D=0;
	else D=2;
	S=3-(G+D);
	pins[G]='G';
	pins[D]='D';
	pins[S]='S';
	return 1;
}

u16 testNMOS()
{
	u32 rON;
	u16 vG,vD;
	u8 D,S,G;
	if(tList[2][0]!=tList[0][0])
	{
		D=tList[2][0];
		S=tList[2][1];
	}
	else
	{
		S=tList[2][0];
		D=tList[2][1];
	}
	G=3-(S+D);
	R_680(D,HIGH);
	R_0(S,LOW);
	R_680(G,LOW);
	Delay_MS(10);
	vG = ReadADC(G);
	if(vG>10) 
	{
		HiZ3(S,D,G);
		return 0; //if gate is lower the vdd it meas current is flowing into it which is not MOS
	}
	vD = ReadADC(D);
	if(vD<1000)
	{
		HiZ3(S,D,G);
		return 0;	//if the VD is higher then 0 when off means its not PMOS
	}
	R_680(G,HIGH);
	Delay_MS(10);
	vG = ReadADC(G);
	if(vG<1000)
	{
		HiZ3(S,D,G);
		return 0; //if gate is higher then 0 it meas current is flowing into it which is not MOS
	}
	vD=ReadADC(D);
	if(vD>123)
	{
		HiZ3(S,D,G);
		return 0;	//if the VD is lower then 0.9*Vdd when ON means its not PMOS
	}
	HiZ3(S,D,G);
	pins[D]='D';
	pins[S]='S';
	pins[G]='G';
	rON=vD*680;
	rON=rON/(1023-vD);
	return (u16)rON;
}

//Tests the part for being PMOS
//first it finds the proper pinout in tList.
//connects the 680R to D LOW, conects S directly to VDD, and Drives the Gate 470K HIGH.
//read both the VG and VD...if VG is~Vdd, and VD is ~0, it brings the VG LOW and reads again..
//This time VG needs to be ~0, and VD~Vdd...if everythinng passes it send the calculated Von resistance at -5V..
u16 testPMOS()
{
	u32 rON;
	u16 vG,vD;
	u8 D,S,G;
	S=tList[2][1];
	D=tList[2][0];
	G=3-(S+D);
	R_680(D,LOW);
	R_0(S,HIGH);
	R_680(G,HIGH);
	Delay_MS(10);
	vG = ReadADC(G);
	if(vG<1000) 
	{
		HiZ3(S,D,G);
		return 0; //if gate is lower the vdd it meas current is flowing into it which is not MOS
	}
	vD = ReadADC(D);
	if(vD>50)
	{
		HiZ3(S,D,G);
		return 0;	//if the VD is higher then 0 when off means its not PMOS
	}
	R_680(G,LOW);
	Delay_MS(10);
	vG = ReadADC(G);
	if(vG>10)
	{
		HiZ3(S,D,G);
		return 0; //if gate is higher then 0 it meas current is flowing into it which is not MOS
	}
	vD=ReadADC(D);
	if(vD<900)
	{
		HiZ3(S,D,G);
		return 0;	//if the VD is lower then 0.9*Vdd when ON means its not PMOS
	}
	HiZ3(S,D,G);
	pins[D]='D';
	pins[S]='S';
	pins[G]='G';
	rON=695640/vD;
	rON=rON-680;
	return (u16)rON;
}

u16 testNPN()
{
	u8 i,C[2],B[2],E[2];
	u16 Vc[2],Vb[2];
	u32 hFE[2];
	B[0]=B[1]=tList[0][0];
	C[0]=E[1]=tList[0][1];
	C[1]=E[0]=tList[1][1];
	R_470K(B[0],HIGH);
	for(i=0;i<2;i++)
	{
		R_680(C[i],HIGH);
		R_0(E[i],LOW);
		Delay_MS(10);
		Vc[i]=1023-ReadADC(C[i]);
		Vb[i]=1023-ReadADC(B[i]);
		hFE[i]=(u32)Vc[i]*691;
		hFE[i]=hFE[i]/Vb[i];
	}
	HiZ3(B[0],C[0],E[0]);
	if(hFE[0]>hFE[1])i=0;
	else i=1;
	pins[C[i]]='C';
	pins[B[i]]='B';
	pins[E[i]]='E';
	return hFE[i];		
}

//reads the Vd and returns it in mV...
u16 testCA()
{
	u8 A,C1,C2;
	u32 vD;
	A=tList[0][0];
	C1=tList[0][1];
	C2=tList[1][1];
	pins[A]='A';
	pins[C1]='C';
	pins[C2]='C';
	vD=tList[0][2]+tList[1][2];
	vD*=2500;	//((Vd1+Vd2)/2)*5000 == (Vd1+vd2)*2500
	vD=vD/1023;
	return vD;
}

u16 testPNP()
{
	u8 i,C[2],B[2],E[2];
	u16 Vc[2],Vb[2];
	u32 hFE[2];
	B[0]=B[1]=tList[0][1];
	C[0]=E[1]=tList[1][0];
	C[1]=E[0]=tList[0][0];
	R_470K(B[0],LOW);
	for(i=0;i<2;i++)
	{
		R_680(C[i],LOW);
		R_0(E[i],HIGH);
		Delay_MS(10);
		Vc[i]=ReadADC(C[i]);
		Vb[i]=ReadADC(B[i]);
		hFE[i]=(u32)Vc[i]*691;
		hFE[i]=hFE[i]/Vb[i];
	}
	HiZ3(B[0],C[0],E[0]);
	if(hFE[0]>hFE[1])i=0;
	else i=1;
	pins[C[i]]='C';
	pins[B[i]]='B';
	pins[E[i]]='E';
	return hFE[i];		
}

//reads the Vd and returns it in mV...
u16 testCC()
{
	u8 C,A1,A2;
	u32 vD;
	C=tList[0][1];
	A1=tList[0][0];
	A2=tList[1][0];
	pins[A1]='A';
	pins[A2]='A';
	pins[C]='C';
	vD=tList[0][2]+tList[1][2];
	vD*=2500;	//((Vd1+Vd2)/2)*5000 == (Vd1+vd2)*2500
	vD=vD/1023;
	return vD;
}

u16 testDIODE()
{
	u8 A,C;
	u32 vD;
	A=tList[0][0];
	C=tList[0][1];
	vD=tList[0][2];
	vD=vD*5000;
	vD=vD/1023;
	pins[A]='A';
	pins[C]='C';
	return vD;
}

u16 testTRIAC()
{
	u8 A,C,G;
	if(nC<8)
	{
		C=node;
		if(C)G=0;
		else G=2;
		A=3-(G+C);
	}
	else
	{
		A=node;
		if(A==1)C=0;
		else
		{
			if(A)C=0;
			else C=2;
		}
		G=3-(A+C);
	}
	pins[A]='A';
	pins[C]='C';
	pins[G]='G';
	if(nC<8)return 1;
	return 2;
}
u16 testSCR()
{
	u32 vG;
	u8 A,C,G;
	G=tList[0][0];
	C=tList[0][1];
	A=3-(C+G);
	pins[G]='G';
	pins[A]='A';
	pins[C]='C';
	if(tList[1][0]=G) vG=tList[1][2];
	else vG= tList[2][2];
	vG=vG*5000;
	vG=vG/1023;
	return vG;
}
u16 testCAP()
{
	
	u32 timer=0,Rtest;
	double cap,RC=0.489484/*0.6952*/,time=0;
	u8 C1,C2,xC;
	testCMP=0;
	
	//due to the way the order of testing is done tListp[0][0] can only be 0 or 1
	//C combos... 0-1,0-2,and 1-2 this is the frst order of tesrting so pin1 and pin2 comparators are assured...
	C1=tList[0][0];
	C2=tList[0][1];
	xC=3-(C1+C2);	//3d unused pin which could be connected to a 2nd comparator need to be brought low
	R_0(xC,LOW);
	//safe Discharege
	R_0(C2,LOW);
	R_680(C1,LOW);
	Delay_MS(100);
	R_0(C1,LOW);
	Delay_MS(10);
	testCMP=1;
	if(tList[0][2]==1023)
	{
		Rtest=470000;
		CMP_INTF=0;	//clear comparator IF
		CMP_INTE=1;	//enable comparator interrupt	
		R_470K(C1,HIGH);
		while(testCMP)
		{
			if(timer<500000)timer++;
			else 
			{
			CMP_INTE=0;
			CMP_INTF=0;
			timer =0;
			break;
			}
		}
	}
	else
	{
		Rtest=680;
		CMP_INTF=0;	//clear comparator IF
		CMP_INTE=1;	//enable comparator interrupt	
		R_680(C1,HIGH);
		while(testCMP)
		{
			if(timer<500000)timer++;
			else 
			{
			CMP_INTE=0;
			CMP_INTF=0;
			timer =0;
			break;
			}
		}	
	}
	
	R_680(C1,LOW);
	Delay_MS(100);
	R_0(C1,LOW);
	HiZ(C2);
	HiZ(C1);
	HiZ(xC);
	pins[C1]='C';
	pins[C2]='C';
	if(timer)			//works down to 7nF..for 470K...up to ~5uF. or 5uF up to ~4mF for 680..
	{	
		if((tList[0][2]==1023)&&(timer>5))timer-=5;
		else timer+=22;
		time=timer*1.6e-6;
		RC=RC*(double)Rtest;
		cap=(double)time/RC;
		cap=cap*1e6;
		if(cap>1)
		{
			unit='u';
		}
		else
		{
			cap=cap*1e3;
			unit='n';
		}
		return (u16)cap;
	}	
	return 0;
}

u16 testRES()
{
	u8 R1,R2,tt;
	u32 r[2],rt680,rt470K,rr;
	u32 t[2]={680,470000};
	R1=tList[0][0];
	R2=tList[0][1];
	R_0(R2,LOW);
	R_680(R1,HIGH);
	Delay_MS(10);	
	r[0] = ReadADC(R1);
	R_470K(R1,HIGH);
	Delay_MS(10);
	r[1] = ReadADC(R1);
	HiZ(R1);
	HiZ(R2);
	if(r[0]>512)rt680=r[0]-512;
	else rt680=512-r[0];

	if(r[1]>512)rt470K=r[1]-512;
	else rt470K=512-r[1];

	if(rt470K>rt680)tt=0;
	else tt=1;
	
	pins[R1]='R';
	pins[R2]='R';
	
	rr=r[tt]*t[tt];
	if(rr==0) return ERROR;
	rr=rr/(1023-r[tt]);
	unit='R';
	if(rr>1000)
	{
		rr/=1000;
		unit = 'K';
	}
	if(rr>1000000)
	{
		rr/=1000000;
		unit = 'M';
	}
	return (u16)rr;
}


u16 testZENER()
{
	u32 vZ;
	u8 A,C,t;
	if(tList[0][2]>tList[1][2])t=0;
	else t=1;

	C=tList[t][0];
	A=tList[t][1];
	vZ=tList[t][2];

	pins[A]='A';
	pins[C]='C';
	
	vZ=vZ*5000;
	vZ=vZ/1023;
	return vZ;
}

u16 testDD()
{
	u8 p1,p2;
	u32 vD;
	p1=tList[0][0];
	p2=tList[0][1];
	pins[p1]='D';
	pins[p2]='D';
	vD=tList[0][2]+tList[1][2];
	vD*=2500;	//((Vd1+Vd2)/2)*5000 == (Vd1+vd2)*2500
	vD=vD/1023;
	return vD;
}





u16 ReadADC(u8 Pin){
	u16 i;
	//setup ADC
	ADCON2=0b10101110; //R justified result, 12TAD time 101, FOSC/64 110 
	//Analog inputs
	//A0-2 are analog monitors
	ADCON1=0b1000; //internal Vrefs, A0-6 analog
	//set channel
	ADCON0=0;
	ADCON0|=((Pin+4)<<2);//enable the channel
	ADCON0|=0b1;//ADON=1
	//take reading
	Delay_MS(1);
	ADCON0|=0b10; //GO/!DONE=1
	while(ADCON0&0b10);
	//return reading
	//i=ADRESH;
	//i=i<<8;
	//i|=ADRESL;
	return ADRES;
}

void quickADCsetup(u8 Pin)
{
	//setup ADC
	ADCON2=0b10001110; //R justified result, 2TAD time 001, FOSC/64 110 
	//Analog inputs
	//A0-2 are analog monitors
	ADCON1=0b1000; //internal Vrefs, A0-6 analog
	//set channel
	ADCON0=0;
	ADCON0|=((Pin+4)<<2);//enable the channel
	ADCON0|=0b1;//ADON=1
	//take reading
	/*Delay_MS(1);
	ADCON0|=0b10; //GO/!DONE=1
	while(ADCON0&0b10);
	//return reading
	//i=ADRESH;
	//i=i<<8;
	//i|=ADRESL;
	return ADRES;*/
}

void Delay_MS(u8 ms){
	static u16 timer;
	u8 i;

	for(i=0; i<ms; i++){
		timer=6000;
		while(timer--);
	}

}

void puts_cdc(rom char *s)
{
	char c;
	while((c = *s++))putc_cdc(c);
}

void putINT_cdc(u16 vcdc)
{

   unsigned int temp,dvd=10000;
   char i=0,k=0;
   temp = vcdc;
	CDC_Flush_In_Now(); 
   for (i=0;i<5;i++)
   {
      temp=vcdc/dvd;
      if(temp)k++;
      if(k)putc_cdc((char)temp + '0');
      vcdc = vcdc - (temp*dvd);
      dvd/=10;
   }
	CDC_Flush_In_Now(); 
}
void tListPrint()
{
	u8 i,j,t1;
	u16 t2;
	puts_cdc("\nnC:");
	putc_cdc(nC+'0');
	puts_cdc("\ndiff:");
	putc_cdc(diff+'0');
	for(i=0;i<nC;i++)
	{	
		puts_cdc("\nCP");
		putc_cdc(i+'1');
		puts_cdc(": ");
		t1=(u8)tList[i][0];
		putc_cdc(t1+'0');
		puts_cdc("->");
		t1=(u8)tList[i][1];
		putc_cdc(t1+'0');
		puts_cdc(" Value: ");
		t2=tList[i][2];
		putINT_cdc(t2);
	}
}

void R_680 (u8 Pin, u8 State){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);
	
	//R0 to input
	R0_DIR|=R0p;
	//470K to input
	R470K_DIR|=R470Kp;
	//680R to direction
	if(State==LOW){
		R680_OUT&=(~(R680p));
	}else{
		R680_OUT|=((R680p));
	}
	//680R to output
	R680_DIR&=(~(R680p));

}
void R_470K (u8 Pin, u8 State){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);

	//R0 to input
	R0_DIR|=R0p;
	//R680 to input
	R680_DIR|=(R680p);
	//470K to direction
	if(State==LOW){
		R470K_OUT&=(~(R470Kp));
	}else{
		R470K_OUT|=(R470Kp);
	}
	//470K to output
	R470K_DIR&=(~(R470Kp));
}
void R_0 (u8 Pin, u8 State){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);

	//680R to input
	R680_DIR|=(R680p);
	//470K to input
	R470K_DIR|=(R470Kp);
	//0R to direction
	if(State==LOW){
		R0_OUT&=(~(R0p));
	}else{
		R0_OUT|=(R0p);
	}
	//0R to output
	R0_DIR&=(~(R0p));
}

void HiZ(u8 Pin){
	u8 R0p, R680p, R470Kp;

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);

	//R0 to input
	R0_DIR|=R0p;
	//680R to input
	R680_DIR|=(R680p);
	//470K to input
	R470K_DIR|=(R470Kp);

}

void HiZ3(u8 A,u8 B, u8 C)
{
	HiZ(A);
	HiZ(B);
	HiZ(C);
}
u16 R_680adc (u8 Pin, u8 State,u16 delay)
{
	u8 R0p, R680p, R470Kp;
	quickADCsetup(Pin);

	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);
	
	//R0 to input
	R0_DIR|=R0p;
	//470K to input
	R470K_DIR|=R470Kp;
	//680R to direction
	if(State==LOW)R680_OUT&=(~(R680p));
	else R680_OUT|=((R680p));
	if(!delay)
	{		
		//680R to output
		R680_DIR&=(~(R680p));
		ADCON0|=0b10; //GO/!DONE=1
		while(ADCON0&0b10);
		//return reading
		//i=ADRESH;
		//i=i<<8;
		//i|=ADRESL;
		return ADRES;
	}
	else
	{
		//680R to output
		R680_DIR&=(~(R680p));
		while(delay--);
		ADCON0|=0b10; //GO/!DONE=1
		while(ADCON0&0b10);
		//return reading
		//i=ADRESH;
		//i=i<<8;
		//i|=ADRESL;
		return ADRES;
	}
}
u16 R_470Kadc (u8 Pin, u8 State,u16 delay)
{
	u8 R0p, R680p, R470Kp;
	quickADCsetup(Pin);
	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);

	//R0 to input
	R0_DIR|=R0p;
	//R680 to input
	R680_DIR|=(R680p);
	//470K to direction
	if(State==LOW)R470K_OUT&=(~(R470Kp));
	else R470K_OUT|=(R470Kp);

	if(!delay)
	{		
		//680R to output
		R470K_DIR&=(~(R680p));
		ADCON0|=0b10; //GO/!DONE=1
		while(ADCON0&0b10);
		//return reading
		//i=ADRESH;
		//i=i<<8;
		//i|=ADRESL;
		return ADRES;
	}
	else
	{
		//680R to output
		R470K_DIR&=(~(R680p));
		while(delay--);
		ADCON0|=0b10; //GO/!DONE=1
		while(ADCON0&0b10);
		//return reading
		//i=ADRESH;
		//i=i<<8;
		//i|=ADRESL;
		return ADRES;
	}
}
u16 HiZadc(u8 Pin,u8 ADCpin,u16 delay)
{
	u8 R0p, R680p, R470Kp;
	quickADCsetup(Pin);
	
	R0p=((1<<Pin)<<3);
	R680p=((1<<Pin));
	R470Kp=(1<<Pin);
	if(!delay)
	{		
		//R0 to input
		R0_DIR|=R0p;
		//680R to input
		R680_DIR|=(R680p);
		//470K to input
		R470K_DIR|=(R470Kp);
		ADCON0|=0b10; //GO/!DONE=1
		while(ADCON0&0b10);
		//return reading
		//i=ADRESH;
		//i=i<<8;
		//i|=ADRESL;
		return ADRES;
	}
	else
	{
		//R0 to input
		R0_DIR|=R0p;
		//680R to input
		R680_DIR|=(R680p);
		//470K to input
		R470K_DIR|=(R470Kp);
		while(delay--);
		ADCON0|=0b10; //GO/!DONE=1
		while(ADCON0&0b10);
		//return reading
		//i=ADRESH;
		//i=i<<8;
		//i|=ADRESL;
		return ADRES;
	}

}

void ProcessingDebug()
{
	u8 low, high;
	putc_cdc(nC);
	putc_cdc(diff);
	putc_cdc(pPartSS);	
	putc_cdc(PartSS);
	low=pins[0];
	putc_cdc(low);
	low=pins[1];
	putc_cdc(low);
	low=pins[2];
	putc_cdc(low);
	if(nC)
	{
		u8 pi;
		for(pi=0;pi<nC;pi++)
		{
			high=tList[pi][0];
			low =tList[pi][1];
			putc_cdc(high);
			putc_cdc(low);
			high=tList[pi][2]>>8;
			low=tList[pi][2];
			putc_cdc(high);
			putc_cdc(low);		
		}
		high=temp>>8;
		low=temp;
		putc_cdc(high);
		putc_cdc(low);
	}
}


/////////////////EOF
