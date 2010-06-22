/*
 * progP12.cpp - algorithms to program the PIC12 (12 bit word) family of microcontrollers
 * Copyright (C) 2009-2010 Alberto Maccioni
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA
 * or see <http://www.gnu.org/licenses/>
 */

void COpenProgDlg::Read12F5xx(int dim, int dim2)
// read 12 bit PIC
// dim=program size 	dim2=config size
// vdd before vpp
// CONFIG @ 0x7FF (upon entering in program mode)
// OSCCAL in last memory location
// 4 ID + reserved area beyond code memory
{
	CString str,aux;
	int size;
	int k=0,z=0,i,j;
	char s[256],t[256];
	if(dim2<4) dim2=4;
	size=0x1000;
	dati_hex.RemoveAll();
	dati_hex.SetSize(size);
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Read12F5xx(%d,%d)\n",dim,dim2);
	}
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T1T2;
	bufferU[j++]=1;						//T1=1u
	bufferU[j++]=100;					//T2=100u
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=2000>>8;
	bufferU[j++]=2000&0xff;
	bufferU[j++]=EN_VPP_VCC;		//enter program mode
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;		//VDD+VPP
	bufferU[j++]=0x5;
	bufferU[j++]=NOP;
	bufferU[j++]=READ_DATA_PROG;	//configuration word
	bufferU[j++]=INC_ADDR;			// 7FF->000
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
	for(z=0;z<DIMBUF-2&&bufferI[z]!=READ_DATA_PROG;z++);
	if(z<DIMBUF-2){
		dati_hex[0xfff]=(bufferI[z+1]<<8)+bufferI[z+2];
		PrintMessage("\r\n");
		PrintMessage1(strings[S_ConfigWord],dati_hex[0xfff]);	//"\r\nConfiguration word: 0x%03X\r\n"
		switch(dati_hex[0xfff]&0x03){
			case 0:
				PrintMessage(strings[S_LPOsc]);	//"LP oscillator\r\n"
				break;
			case 1:
				PrintMessage(strings[S_XTOsc]);	//"XT oscillator\r\n"
				break;
			case 2:
				PrintMessage(strings[S_IntOsc]);	//"Internal osc.\r\n"
				break;
			case 3:
				PrintMessage(strings[S_RCOsc]);	//"RC oscillator\r\n"
				break;
		}
		if(dati_hex[0xfff]&0x04) PrintMessage(strings[S_WDTON]);	//"WDT ON\r\n"
		else PrintMessage(strings[S_WDTOFF]);	//"WDT OFF\r\n"
		if(dati_hex[0xfff]&0x08) PrintMessage(strings[S_CPOFF]);	//"Code protection OFF\r\n"
		else PrintMessage(strings[S_CPON]);	//"Code protection ON\r\n"
		if(dati_hex[0xfff]&0x10) PrintMessage(strings[S_MCLRON]);	//"Master clear ON\r\n"
		else PrintMessage(strings[S_MCLROFF]);	//"Master clear OFF\r\n"
	}
	else PrintMessage(strings[S_NoConfigW]);	//"Impossibile leggere la config word\r\n"
//****************** read code ********************
	PrintMessage(strings[S_CodeReading1]);		//lettura codice ...
	for(i=0,j=1;i<dim+dim2;i++){
		bufferU[j++]=READ_DATA_PROG;
		bufferU[j++]=INC_ADDR;
		if(j>DIMBUF*2/4-2||i==dim+dim2-1){		//2 istruzioni -> 4 risposte
			bufferU[j++]=FLUSH;
			for(;j<DIMBUF;j++) bufferU[j]=0x0;
			write();
			msDelay(5);
			read();
			for(z=1;z<DIMBUF-2;z++){
				if(bufferI[z]==READ_DATA_PROG){
					dati_hex[k++]=(bufferI[z+1]<<8)+bufferI[z+2];
					z+=2;
				}
			}
			PrintStatus(strings[S_CodeReading],i*100/(dim+dim2),i);	//"Read: %d%%, addr. %03X"
			j=1;
			if(saveLog){
				fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
				WriteLogIO();
			}
		}
	}
	bufferU[j++]=NOP;				//uscita program mode
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(1);
	read();
	unsigned int stop=GetTickCount();
	if(saveLog)CloseLogFile();
	for(i=k;i<0xfff;i++) dati_hex[i]=0xfff;
	if(k!=dim+dim2){
		PrintMessage2(strings[S_ReadErr],dim+dim2,k);	//"Errore in lettura: word richieste=%d, lette=%d\r\n"
	}
	else PrintMessage1(strings[S_Compl],k);	//"completed\n"
//****************** visualize ********************
	for(i=0;i<4;i+=2){
		PrintMessage4(strings[S_ChipID],i,dati_hex[dim+i],i+1,dati_hex[dim+i+1]);	//"ID%d: 0x%03X   ID%d: 0x%03X\r\n"
	}
	if(dim2>4){
		PrintMessage1(strings[S_BKOsccal],dati_hex[dim+4]);	//"Backup OSCCAL: 0x%03X\r\n"
	}
	PrintMessage("\r\n");
	PrintMessage(strings[S_CodeMem]);	//"\r\nMemoria programma:\r\n"
	s[0]=0;
	int valid=0,empty=1;
	for(i=0;i<dim;i+=COL){
		valid=0;
		for(j=i;j<i+COL&&j<dim;j++){
			sprintf(t,"%03X ",dati_hex[j]);
			strcat(s,t);
			if(dati_hex[j]<0xfff) valid=1;
		}
		if(valid){
			sprintf(t,"%04X: %s\r\n",i,s);
			empty=0;
			aux+=t;
		}
		s[0]=0;
	}
	if(empty) PrintMessage(strings[S_Empty]);	//empty
	else PrintMessage(aux);
	aux.Empty();
	if(dim2>5){
		PrintMessage(strings[S_ConfigResMem]);	//"\r\nMemoria configurazione e riservata:\r\n"
		empty=1;
		for(i=dim;i<dim+dim2;i+=COL){
			valid=0;
			for(j=i;j<i+COL&&j<dim+64;j++){
				sprintf(t,"%03X ",dati_hex[j]);
				strcat(s,t);
				if(dati_hex[j]<0xfff) valid=1;
			}
			if(valid){
				sprintf(t,"%04X: %s\r\n",i,s);
				empty=0;
				aux+=t;
			}
			s[0]=0;
		}
		if(empty) PrintMessage(strings[S_Empty]);	//empty
		else PrintMessage(aux);
	}
	StatusBar.SetWindowText("");
	PrintMessage("\r\n");
	PrintMessage1(strings[S_End],(stop-start)/1000.0);	//"\r\nEnd (%.2f s)\r\n"

}

void COpenProgDlg::Write12F5xx(int dim,int OscAddr)
{
// write 12 bit PIC
// dim=program size     max~4300=10CC
// OscAddr=OSCCAL address (saved at the beginning), -1 not to use it
// vdd before vpp
// CONFIG @ 0x7FF upon entering program mode
// BACKUP OSCCAL @ dim+5 (saved at the beginning)
// erase: BULK_ERASE_PROG (1001) +10ms
// write: BEGIN_PROG (1000) + Tprogram 2ms + END_PROG2 (1110);
	CString str;
	int usa_BKosccal,usa_osccal,size;
	int k=0,z=0,i,j,w;
	int err=0;
	WORD osccal=-1,BKosccal=-1;
	if(OscAddr>dim) OscAddr=dim-1;
	CButton* b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_OSCCAL);
	usa_osccal=b->GetCheck();
	b=(CButton*)m_DispoPage.GetDlgItem(IDC_OSC_BK);
	usa_BKosccal=b->GetCheck();
	size=dati_hex.GetSize();
	if(OscAddr==-1) usa_BKosccal=usa_osccal=0;
	if(size<0x1000){
		PrintMessage(strings[S_NoConfigW2]);	//"Impossibile trovare la locazione CONFIG (0xFFF)\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Write12F5xx(%d,%d)\n",dim,OscAddr);
	}
	for(i=0;i<size;i++) dati_hex[i]&=0xFFF;
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T1T2;
	bufferU[j++]=1;						//T1=1u
	bufferU[j++]=100;					//T2=100u
	bufferU[j++]=EN_VPP_VCC;		//enter program mode
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;		//VDD+VPP
	bufferU[j++]=0x5;
	bufferU[j++]=NOP;
	if(OscAddr!=-1){
		for(i=-1;i<OscAddr-0xff;i+=0xff){
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=0xff;
		}
		bufferU[j++]=INC_ADDR_N;
		bufferU[j++]=OscAddr-i;
		bufferU[j++]=READ_DATA_PROG;	// OSCCAL
		if(OscAddr<dim){
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=dim-OscAddr;
		}
		bufferU[j++]=INC_ADDR_N;
		bufferU[j++]=0x4;				// 400->404
		bufferU[j++]=READ_DATA_PROG;	// backup OSCCAL
	}
	bufferU[j++]=NOP;				//uscita program mode
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=10000>>8;
	bufferU[j++]=10000&0xff;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(15);
	read();
	if(saveLog)WriteLogIO();
	if(OscAddr!=-1){
		for(z=4;z<DIMBUF-2&&bufferI[z]!=READ_DATA_PROG;z++);
		if(z<DIMBUF-2) osccal=(bufferI[z+1]<<8)+bufferI[z+2];
		for(z+=3;z<DIMBUF-2&&bufferI[z]!=READ_DATA_PROG;z++);
		if(z<DIMBUF-2) BKosccal=(bufferI[z+1]<<8)+bufferI[z+2];
		if(osccal==-1||BKosccal==-1){
			PrintMessage(strings[S_ErrOsccal]);	//"Errore in lettura OSCCAL e BKOSCCAL"
			PrintMessage("\r\n");
			return;
		}
		PrintMessage1(strings[S_Osccal],osccal);	//"OSCCAL: 0x%03X\r\n"
		PrintMessage1(strings[S_BKOsccal],BKosccal);	//"Backup OSCCAL: 0x%03X\r\n"
	}
//****************** erase memory ********************
	PrintMessage(strings[S_StartErase]);	//"Cancellazione ... "
	j=1;
	bufferU[j++]=EN_VPP_VCC;			// enter program mode
	bufferU[j++]=0x1;
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x5;
	if(dim>OscAddr+1){				//12F519 (Flash+EEPROM)
		bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
		bufferU[j++]=WAIT_T3;			// delay T3=10ms
		for(i=-1;i<dim-0xff;i+=0xff){	// 0x43F
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=0xff;
		}
		bufferU[j++]=INC_ADDR_N;
		bufferU[j++]=dim-i-1;
		bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase EEPROM
		bufferU[j++]=WAIT_T3;			// delay T3=10ms
		if(programID){
			bufferU[j++]=INC_ADDR;
			bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
			bufferU[j++]=WAIT_T3;			// delay T3=10ms
		}
	}
	else{							//12Fxxx
		if(programID){
			for(i=-1;i<dim-0xff;i+=0xff){
				bufferU[j++]=INC_ADDR_N;
				bufferU[j++]=0xff;
			}
			bufferU[j++]=INC_ADDR_N;
			bufferU[j++]=dim-i;
			bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
			bufferU[j++]=WAIT_T3;			// delay T3=10ms
		}
		else{
			bufferU[j++]=BULK_ERASE_PROG;	// Bulk erase
			bufferU[j++]=WAIT_T3;			// delay T3=10ms
		}
	}
	bufferU[j++]=EN_VPP_VCC;		// uscita program mode
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=WAIT_T3;			// delay T3=10ms before entering program mode
	bufferU[j++]=EN_VPP_VCC;		// enter program mode
	bufferU[j++]=0x1;
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x5;
	bufferU[j++]=INC_ADDR;				// 7FF->000
	bufferU[j++]=SET_PARAMETER;
	bufferU[j++]=SET_T3;
	bufferU[j++]=2000>>8;				//T3=2ms
	bufferU[j++]=2000&0xff;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(30);
	if(dim>OscAddr+1) msDelay(20);
	read();
	PrintMessage(strings[S_Compl]);	//"completed\r\n"
	if(saveLog)WriteLogIO();
//****************** write code ********************
	PrintMessage(strings[S_StartCodeProg]);	//"Scrittura codice ... "
	int dim1=dim;
	if(programID) dim1=dim+5;
	if(dati_hex[dim+4]>=0xFFF) dati_hex[dim+4]=BKosccal;  //reload BKosccal if not present
	if(usa_BKosccal) dati_hex[OscAddr]=BKosccal;
	else if(usa_osccal) dati_hex[OscAddr]=osccal;
	for(i=k=w=0,j=1;i<dim1;i++){
		if(dati_hex[i]<0xfff){
			bufferU[j++]=LOAD_DATA_PROG;
			bufferU[j++]=dati_hex[i]>>8;		//MSB
			bufferU[j++]=dati_hex[i]&0xff;		//LSB
			bufferU[j++]=BEGIN_PROG;
			bufferU[j++]=WAIT_T3;				//Tprogram 2ms
			bufferU[j++]=END_PROG2;
			bufferU[j++]=WAIT_T2;				//Tdischarge
			bufferU[j++]=READ_DATA_PROG;
			w++;
		}
		bufferU[j++]=INC_ADDR;
		if(j>DIMBUF-10||i==dim1-1){
			PrintStatus(strings[S_CodeWriting],i*100/dim,i);	//"Write: %d%%, ind. %03X"
			bufferU[j++]=FLUSH;
			for(;j<DIMBUF;j++) bufferU[j]=0x0;
			write();
			msDelay(w*3+3);
			w=0;
			read();
			for(z=1;z<DIMBUF-7;z++){
				if(bufferI[z]==INC_ADDR&&dati_hex[k]>=0xfff) k++;
				else if(bufferI[z]==LOAD_DATA_PROG&&bufferI[z+5]==READ_DATA_PROG){
					if (dati_hex[k]!=(bufferI[z+6]<<8)+bufferI[z+7]){
						PrintMessage("\r\n");
						PrintMessage3(strings[S_CodeWError],k,dati_hex[k],(bufferI[z+6]<<8)+bufferI[z+7]);	//"Errore in scrittura all'indirizzo %3X: scritto %03X, letto %03X\r\n"
						err++;
						if(max_err&&err>max_err){
							PrintMessage1(strings[S_MaxErr],err);	//"Exceeded maximum number of errors (%d), write interrupted\r\n"
							PrintMessage(strings[S_IntW]);	//"write interrupted"
							i=dim1;
							z=DIMBUF;
						}
					}
					k++;
					z+=8;
				}
			}
			j=1;
			if(saveLog){
				fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, errori=%d\n"
				WriteLogIO();
			}
		}
	}
	err+=i-k;
	PrintMessage1(strings[S_ComplErr],err);	//"completed, %d errors\r\n"
//****************** write CONFIG ********************
	PrintMessage(strings[S_ConfigW]);	//"Write CONFIG ... "
	int err_c=0;
	bufferU[j++]=NOP;				//uscita program mode
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=WAIT_T3;			//10 ms tra uscita e rientro prog. mode
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=WAIT_T3;
	bufferU[j++]=EN_VPP_VCC;		//enter program mode
	bufferU[j++]=0x1;
	bufferU[j++]=NOP;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x5;
	bufferU[j++]=LOAD_DATA_PROG;	//config word
	bufferU[j++]=dati_hex[0xfff]>>8;			//MSB
	bufferU[j++]=dati_hex[0xfff]&0xff;			//LSB
	bufferU[j++]=BEGIN_PROG;
	bufferU[j++]=WAIT_T3;			//Tprogram 2ms
	bufferU[j++]=END_PROG2;
	bufferU[j++]=WAIT_T2;			//Tdischarge
	bufferU[j++]=READ_DATA_PROG;
	bufferU[j++]=NOP;				//uscita program mode
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x1;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=SET_CK_D;
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(20);
	read();
	unsigned int stop=GetTickCount();
	for(z=10;z<DIMBUF-2&&bufferI[z]!=READ_DATA_PROG;z++);
	if (~dati_hex[0xfff]&((bufferI[z+1]<<8)+bufferI[z+2])){	//error if written 0 and read 1 (~W&R)
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ConfigWErr],dati_hex[0xfff],(bufferI[z+1]<<8)+bufferI[z+2]);	//"Errore in Write CONFIG:\r\ndato scritto %03X, letto %03X\r\n"
		err_c++;
	}
	err+=err_c;
	if (z>DIMBUF-2){
		PrintMessage("\r\n");
		PrintMessage(strings[S_ConfigWErr2]);	//"Error writing CONFIG"
	}
	PrintMessage1(strings[S_ComplErr],err_c);	//"completed, %d errors\r\n"
	if(saveLog){
		fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, errori=%d\n"
		WriteLogIO();
		CloseLogFile();
	}
	PrintMessage3(strings[S_EndErr],(stop-start)/1000.0,err,err!=1?strings[S_ErrPlur]:strings[S_ErrSing]);	//"\r\nFine (%.2f s) %d %s\r\n\r\n"
	StatusBar.SetWindowText("");
}

