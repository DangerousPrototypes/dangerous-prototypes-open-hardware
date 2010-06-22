/*
 * progEEPROM.cpp - algorithms to program various EEPROM types
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

void COpenProgDlg::ReadI2C(int dim,int addr=0)
// read I2C memories
// dim=size in bytes		
// addr:
//      [3:0]  =0: 1 byte address        =1: 2 byte address
//      [7:4]  A2:A0 value
//      [11:8] 17th address bit location (added to control byte)
{
	CString str;
	hvreg=0;
	int k=0,z=0,i,j;
	int AX=(addr>>4)&7;
	int addr17=(addr>>8)&0xF;
	addr&=1;
	if(dim>0x30000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"ReadI2C(%d,%d)    (0x%X,0x%X)\n",dim,addr,dim,addr);
	}
	memEE.RemoveAll();
	memEE.SetSize(dim);			//EEPROM
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=I2C_INIT;
	bufferU[j++]=AX;			//100k
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
//****************** read ********************
	PrintMessage(strings[S_ReadEE]);		//read EEPROM ...
	for(i=0,j=1;i<dim;i+=DIMBUF-4){
		if(!addr){									//1 byte address
			bufferU[j++]=I2C_READ;
			bufferU[j++]=i<dim-(DIMBUF-4)?DIMBUF-4:dim-i;
			bufferU[j++]=0xA0+(i>>7&0x0E);
			bufferU[j++]=i&0xFF;
		}
		else{										//2 bytes address
			bufferU[j++]=I2C_READ2;
			bufferU[j++]=i<dim-(DIMBUF-4)?DIMBUF-4:dim-i;
			bufferU[j++]=0xA0+(i>0xFFFF?addr17:0); //17th bit if>64K
			bufferU[j++]=(i>>8)&0xFF;
			bufferU[j++]=i&0xFF;
		}
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(8);
		read();
		if((bufferI[1]==I2C_READ||bufferI[1]==I2C_READ2)&&bufferI[2]<0xFA){
			for(z=3;z<bufferI[2]+3&&z<DIMBUF;z++) memEE[k++]=bufferI[z];
		}
		PrintStatus(strings[S_CodeReading2],i*100/(dim),i);	//"Read: %d%%, addr. %05X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
			WriteLogIO();
		}
	}
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
		memEE.SetSize(k);
	}
	else PrintMessage(strings[S_Compl]);
//****************** exit ********************
	bufferU[j++]=EN_VPP_VCC;		//0
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	DisplayEE();	//visualize
	PrintMessage1(strings[S_End],(stop-start)/1000.0);	//"\r\nEnd (%.2f s)\r\n"
	if(saveLog) CloseLogFile();
}

void COpenProgDlg::WriteI2C(int dim,int addr=0,int page=16, float wait=5.0)
// write I2C memories
// dim=size in bytes
// addr:
//      [3:0]  =0: 1 byte address        =1: 2 byte address
//      [7:4]  A2:A0 value
//      [11:8] 17th address bit location (added to control byte)
// page=page size		
// wait=write delay (ms)
{
	CString str;
	int sizeEE=memEE.GetSize();
	hvreg=0;
	int k=0,z=0,i,j;
	int err=0;
	int AX=(addr>>4)&7;
	int addr17=(addr>>8)&0xF;
	addr&=1;
	if(dim>0x30000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"WriteI2C(%d,%d,%d,%f)    (0x%X,0x%X)\n",dim,addr,page,wait,dim,addr);
	}
	if(dim>sizeEE){
		i=sizeEE;
		memEE.SetSize(dim);
		for(;i<dim;i++) memEE[i]=0xFF;
		sizeEE=dim;
	}
	if(dim<1){
		PrintMessage(strings[S_NoCode]);	//"Data area is empty\r\n"
		return;
	}
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=I2C_INIT;
	bufferU[j++]=AX;			//100k
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
//****************** write ********************
	PrintMessage(strings[S_EEAreaW]);	//"Write EEPROM ... "
	for(;page>=DIMBUF-6;page>>=1);
	for(i=0,j=1;i<dim;i+=page){
		bufferU[j++]=I2C_WRITE;
		if(!addr){									//1 byte address
			bufferU[j++]=page;
			bufferU[j++]=0xA0+(i>>7&0x0E);
			bufferU[j++]=i&0xFF;
		}
		else{										//2 bytes address
			bufferU[j++]=page+1;
			bufferU[j++]=0xA0+(i>0xFFFF?addr17:0); //17th bit if>64K
			bufferU[j++]=(i>>8)&0xFF;
			bufferU[j++]=i&0xFF;
		}
		for(k=0;k<page;k++) bufferU[j++]=memEE[i+k];
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(wait+1);
		read();
		if(bufferI[1]!=I2C_WRITE||bufferI[2]>=0xFA) i=dim+10;
		PrintStatus(strings[S_CodeWriting2],i*100/(dim),i);	//"Write: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
			WriteLogIO();
		}
	}
	PrintMessage(strings[S_Compl]);	//"completed\r\n"
//****************** verify EEPROM ********************
	PrintMessage(strings[S_EEV]);	//"Verify EEPROM ... "
	k=0;
	for(i=0,j=1;i<dim;i+=DIMBUF-4){
		if(!addr){									//1 byte address
			bufferU[j++]=I2C_READ;
			bufferU[j++]=i<dim-(DIMBUF-4)?DIMBUF-4:dim-i;
			bufferU[j++]=0xA0+(i>>7&0x0E);
			bufferU[j++]=i&0xFF;
		}
		else{										//2 bytes address
			bufferU[j++]=I2C_READ2;
			bufferU[j++]=i<dim-(DIMBUF-4)?DIMBUF-4:dim-i;
			bufferU[j++]=0xA0+(i>0xFFFF?addr17:0); //17th bit if>64K
			bufferU[j++]=(i>>8)&0xFF;
			bufferU[j++]=i&0xFF;
		}
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(8);
		read();
		if((bufferI[1]==I2C_READ||bufferI[1]==I2C_READ2)&&bufferI[2]<0xFA){
			for(z=3;z<bufferI[2]+3&&z<DIMBUF;z++){
				if(memEE[k++]!=bufferI[z]){
					PrintMessage("\r\n");
					PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k-1],bufferI[z]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
					err++;
				}
			}
		}
		PrintStatus(strings[S_CodeV2],i*100/(dim),i);	//"Verify: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, err=%d\n"
			WriteLogIO();
		}
		if(err>=max_err) break;
	}
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
	}
	PrintMessage1(strings[S_ComplErr],err);	//"completed: %d errors\r\n"
//****************** exit ********************
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	PrintMessage3(strings[S_EndErr],(stop-start)/1000.0,err,err!=1?strings[S_ErrPlur]:strings[S_ErrSing]);	//"\r\nEnd (%.2f s) %d %s\r\n\r\n"
	if(saveLog) CloseLogFile();
}

#define PRE 0x08	//RB3
#define S 0x10		//RB4
#define W 0x20		//RB5
#define ORG 0x20	//RB5

void COpenProgDlg::Read93x(int dim,int na=8,int options=0)
// read 93Sx6 uW memories
// dim=size in bytes
// na=address bits
// options=0: x16 organization     =1: x8 organization
{
	CString str;
	int sizeEE;
	hvreg=0;
	int k=0,z=0,i,j;
	if(dim>0x3000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(na>13) na=13;
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Read93x(%d,%d,%d)    (0x%X,0x%X)\n",dim,na,options,dim,na);
	}
	sizeEE=dim;
	memEE.RemoveAll();
	memEE.SetSize(dim);			//EEPROM
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=uW_INIT;
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?S+ORG:S;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;				//READ
	bufferU[j++]=0xC0;				//110aaaaa aaax0000 
	bufferU[j++]=0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
//****************** read ********************
	PrintMessage(strings[S_ReadEE]);		//read EEPROM ...
	int n=(DIMBUF-2);
	if(n>30) n=30;				//max 240 bit = 30 Byte
	for(i=0,j=1;i<dim;i+=n){
		bufferU[j++]=uWRX;
		bufferU[j++]=i<(dim-n)?n*8:(dim-i)*8;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(2);
		read();
		if(bufferI[1]==uWRX){
			for(j=3;j<bufferI[2]/8+3&&j<DIMBUF;j++){
				memEE[k++]=bufferI[j];
			}
		}
		PrintStatus(strings[S_CodeReading2],i*100/(dim),i);	//"Read: %d%%, addr. %05X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
			WriteLogIO();
		}
	}	
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
		memEE.SetSize(k);
	}
	else PrintMessage(strings[S_Compl]);
	if(options==0){
		for(i=0;i<dim;i+=2){		//swap bytes
			k=memEE[i];
			memEE[i]=memEE[i+1];
			memEE[i+1]=k;
		}
	}
//****************** exit ********************
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0;
	bufferU[j++]=0;
	bufferU[j++]=EN_VPP_VCC;		//0
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	DisplayEE();	//visualize
	PrintMessage1(strings[S_End],(stop-start)/1000.0);	//"\r\nEnd (%.2f s)\r\n"
	if(saveLog) CloseLogFile();
}

void COpenProgDlg::Write93Sx(int dim,int na=8,int page=8, double wait=5.0)
// write 93Sx6 uW memories
// dim=size in bytes
// na=address bits
// page=page size (bytes)
// wait=write delay
{
	CString str;
	int sizeEE=memEE.GetSize();
	hvreg=0;
	int k=0,z=0,i,j;
	int err=0;
	if(dim>0x1000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(na>13) na=13;
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Write93Sx(%d,%d,%d,%f)    (0x%X,0x%X)\n",dim,na,page,wait,dim,na);
	}
	if(dim>sizeEE){
		i=sizeEE;
		memEE.SetSize(dim);
		for(;i<dim;i++) memEE[i]=0xFF;
		sizeEE=dim;
	}
	if(dim<1){
		PrintMessage(strings[S_NoCode]);	//"Data area is empty\r\n"
		return;
	}
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0;
	bufferU[j++]=0;
	bufferU[j++]=uW_INIT;
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=S+W+PRE;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;
	bufferU[j++]=0x98;				//100 11xxx Prot. reg. enable
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=W+PRE;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=S+W+PRE;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;
	bufferU[j++]=0xFF;				//111 11111111 Prot. reg. clear
	bufferU[j++]=0xF0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=W+PRE;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=S+W;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;
	bufferU[j++]=0x98;				//100 11xxx write enable
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=W+PRE;
	bufferU[j++]=0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
//****************** write ********************
	PrintMessage(strings[S_EEAreaW]);	//"Write EEPROM ... "
	int addr=0;
	for(i=0,j=1;i<dim;i+=page,addr+=(0x10000>>na)*page/2){
		bufferU[j++]=EXT_PORT;
		bufferU[j++]=S+W;
		bufferU[j++]=0;
		bufferU[j++]=uWTX;
		bufferU[j++]=3;
		bufferU[j++]=0xE0;			//111aaaaa aaa(a) D page write
		bufferU[j++]=uWTX;
		bufferU[j++]=na;
		bufferU[j++]=addr>>8;
		if(na>8) bufferU[j++]=addr&0xFF;
		bufferU[j++]=uWTX;
		bufferU[j++]=8*page;
		for(k=0;k<page;k+=2){
			bufferU[j++]=memEE[i+k+1];
			bufferU[j++]=memEE[i+k];
		}
		bufferU[j++]=EXT_PORT;
		bufferU[j++]=W;
		bufferU[j++]=0;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(wait+1);
		read();
		if(bufferI[2]!=uWTX||bufferI[3]>=0xFA) i=dim+10;
		PrintStatus(strings[S_CodeWriting2],i*100/(dim),i);	//"Write: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
			WriteLogIO();
		}
	}
	msDelay(wait+1);
	PrintMessage(strings[S_Compl]);	//"completed\r\n"
//****************** verify EEPROM ********************
	PrintMessage(strings[S_EEV]);	//"Verify EEPROM ... "
	bufferU[0]=0;
	j=1;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=S;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;				//READ (16bit)
	bufferU[j++]=0xC0;				//110aaaaa aaax0000
	bufferU[j++]=0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
	k=0;
	int n=(DIMBUF-2);
	if(n>30) n=30;	//max 240 bit = 30 Byte
	for(i=0,j=1;i<dim;i+=n){
		bufferU[j++]=uWRX;
		bufferU[j++]=i<(dim-n)?n*8:(dim-i)*8;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(2);
		read();
		if(bufferI[1]==uWRX&&bufferI[2]<0xFA){
			for(z=3;z<bufferI[2]/8+3&&z<DIMBUF;z+=2,k+=2){
				if(memEE[k+1]!=bufferI[z]){
					PrintMessage("\r\n");
					PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k+1],bufferI[z]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
					err++;
				}
				if(memEE[k]!=bufferI[z+1]){
					PrintMessage("\r\n");
					PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k],bufferI[z+1]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
					err++;
				}
			}
		}
		PrintStatus(strings[S_CodeV2],i*100/(dim),i);	//"Verify: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, err=%d\n"
			WriteLogIO();
		}
		if(err>=max_err) break;
	}
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
	}
	PrintMessage1(strings[S_ComplErr],err);	//"completed: %d errors\r\n"
//****************** exit ********************
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0;
	bufferU[j++]=0;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	PrintMessage3(strings[S_EndErr],(stop-start)/1000.0,err,err!=1?strings[S_ErrPlur]:strings[S_ErrSing]);	//"\r\nEnd (%.2f s) %d %s\r\n\r\n"
	if(saveLog) CloseLogFile();
}

void COpenProgDlg::Write93Cx(int dim,int na=8,int options=0)
// write 93Cx6 uW memories
// dim=size in bytes
// na=address bits
// options=0: x16 organization     =1: x8 organization
{
	CString str;
	int sizeEE=memEE.GetSize();
	hvreg=0;
	int k=0,z=0,i,j;
	int err=0;
	if(dim>0x1000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(na>13) na=13;
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Write93Cx(%d,%d,%d)    (0x%X,0x%X)\n",dim,na,options,dim,na);
	}
	if(dim>sizeEE){
		i=sizeEE;
		memEE.SetSize(dim);
		for(;i<dim;i++) memEE[i]=0xFF;
		sizeEE=dim;
	}
	if(dim<1){
		PrintMessage(strings[S_NoCode]);	//"Data area is empty\r\n"
		return;
	}
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0;
	bufferU[j++]=0;
	bufferU[j++]=uW_INIT;
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?S+ORG+PRE:S+PRE;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;
	bufferU[j++]=0x98;				//100 11xxx EWEN
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?ORG+PRE:PRE;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?S+ORG+PRE:S+PRE;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;
	bufferU[j++]=0x90;				//100 10xxx ERAL
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?ORG+PRE:PRE;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?S+ORG+PRE:S+PRE;
	bufferU[j++]=0;
	bufferU[j++]=uWRX;
	bufferU[j++]=1;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
	j=1;
	bufferU[j++]=uWRX;
	bufferU[j++]=1;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	for(i=0,k=0;i<30&&!k;i++){		//Wait until ready
		write();
		msDelay(2);
		read();
		if(saveLog)WriteLogIO();
		k=bufferI[3];
	}
//****************** write ********************
	PrintMessage(strings[S_EEAreaW]);	//"Write EEPROM ... "
	int addr=0;
	j=1;
	for(i=0;i<dim;i+=options==0?2:1,addr+=0x10000>>na){
		if(memEE[i]<0xFF||(options==0&&memEE[i+1]<0xFF)){
			bufferU[j++]=uWTX;
			bufferU[j++]=3;
			bufferU[j++]=0xA0;			//101aaaaa aaa(a) write
			bufferU[j++]=uWTX;
			bufferU[j++]=na;
			bufferU[j++]=addr>>8;
			if(na>8) bufferU[j++]=addr&0xFF;
			bufferU[j++]=uWTX;
			if(options==0){		//x16
				bufferU[j++]=16;
				bufferU[j++]=memEE[i+1];
				bufferU[j++]=memEE[i];
			}
			else{				//x8
				bufferU[j++]=8;
				bufferU[j++]=memEE[i];
			}
			bufferU[j++]=EXT_PORT;
			bufferU[j++]=options==0?ORG+PRE:PRE;
			bufferU[j++]=0;
			bufferU[j++]=EXT_PORT;
			bufferU[j++]=options==0?S+ORG+PRE:S+PRE;
			bufferU[j++]=0;
			bufferU[j++]=uWRX;
			bufferU[j++]=1;
			bufferU[j++]=FLUSH;
			for(;j<DIMBUF;j++) bufferU[j]=0x0;
			write();
			msDelay(1.5);
			read();
			if(bufferI[1]!=uWTX||bufferI[2]>=0xFA) i=dim+10;
			PrintStatus(strings[S_CodeWriting2],i*100/(dim),i);	//"Write: %d%%, addr. %04X"
			j=1;
			if(saveLog){
				fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
				WriteLogIO();
			}
			bufferU[j++]=uWRX;
			bufferU[j++]=1;
			bufferU[j++]=FLUSH;
			for(;j<DIMBUF;j++) bufferU[j]=0x0;
			for(z=0,k=0;z<30&&!k;z++){		//Wait until ready
				write();
				msDelay(1.5);
				read();
				if(saveLog)WriteLogIO();
				k=bufferI[3];
			}
			j=1;
		}
	}
	msDelay(1);
	if(i!=dim){
		PrintMessage2(strings[S_CodeWError4],i,dim);	//"Error writing code area, requested %d bytes, read %d\r\n"
	}
	else PrintMessage(strings[S_Compl]);	//"completed\r\n"
//****************** verify EEPROM ********************
	PrintMessage(strings[S_EEV]);	//"Verify EEPROM ... "
	j=1;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?ORG+PRE:PRE;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?S+ORG+PRE:S+PRE;
	bufferU[j++]=0;
	bufferU[j++]=FLUSH;
	write();
	msDelay(1.5);
	read();
	if(saveLog)WriteLogIO();/**/
	bufferU[0]=0;
	j=1;
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=options==0?S+ORG:S;
	bufferU[j++]=0;
	bufferU[j++]=uWTX;
	bufferU[j++]=na+3;				//READ (16bit)
	bufferU[j++]=0xC0;				//110aaaaa aaax0000
	bufferU[j++]=0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
	k=0;
	int n=(DIMBUF-2);
	if(n>30) n=30;	//max 240 bit = 30 Byte
	for(i=0,j=1;i<dim;i+=n){
		bufferU[j++]=uWRX;
		bufferU[j++]=i<(dim-n)?n*8:(dim-i)*8;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(2);
		read();
		if(options==0){		//x16
			if(bufferI[1]==uWRX&&bufferI[2]<0xFA){
				for(z=3;z<bufferI[2]/8+3&&z<DIMBUF;z+=2,k+=2){
					if(memEE[k+1]!=bufferI[z]){
						PrintMessage("\r\n");
						PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k+1],bufferI[z]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
						err++;
					}
					if(memEE[k]!=bufferI[z+1]){
						PrintMessage("\r\n");
						PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k],bufferI[z+1]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
						err++;
					}
				}
			}
		}
		else{				//x8
			if(bufferI[1]==uWRX&&bufferI[2]<0xFA){
				for(z=3;z<bufferI[2]/8+3&&z<DIMBUF;z++,k++){
					if(memEE[k]!=bufferI[z]){
						PrintMessage("\r\n");
						PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k],bufferI[z]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
						err++;
					}
				}
			}
		}
		PrintStatus(strings[S_CodeV2],i*100/(dim),i);	//"Verify: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, err=%d\n"
			WriteLogIO();
		}
		if(err>=max_err) break;
	}
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
	}
	PrintMessage1(strings[S_ComplErr],err);	//"completed: %d errors\r\n"
//****************** exit ********************
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0;
	bufferU[j++]=0;
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	PrintMessage3(strings[S_EndErr],(stop-start)/1000.0,err,err!=1?strings[S_ErrPlur]:strings[S_ErrSing]);	//"\r\nEnd (%.2f s) %d %s\r\n\r\n"
	if(saveLog) CloseLogFile();
}

#define CS 8
#define HLD 16		//Hold
#define WP 0x40		//Write protect

void COpenProgDlg::Read25xx(int dim)
// read 25xx SPI memories
// dim=size in bytes
{
	CString str;
	int sizeEE;
	hvreg=0;
	int k=0,z=0,i,j;
	if(dim>0x1000000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Read25xx(%d)    (0x%X)\n",dim,dim);
	}
	sizeEE=dim;
	memEE.RemoveAll();
	memEE.SetSize(dim);			//EEPROM
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=SPI_INIT;
	bufferU[j++]=2;				//0=100k, 1=200k, 2=300k
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EXT_PORT;	//CS=1, HLD=1, WP=0
	bufferU[j++]=CS+HLD;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;	//CS=0, HLD=1, WP=0
	bufferU[j++]=HLD;
	bufferU[j++]=0;
	bufferU[j++]=SPI_WRITE;		//Read
	if(dim>0x10000){				//24 bit address
		bufferU[j++]=4;
		bufferU[j++]=3;
		bufferU[j++]=0;
		bufferU[j++]=0;
		bufferU[j++]=0;
	}
	else if(dim>0x200){				//16 bit address
		bufferU[j++]=3;
		bufferU[j++]=3;
		bufferU[j++]=0;
		bufferU[j++]=0;
	}
	else{						//8 bit address
		bufferU[j++]=2;
		bufferU[j++]=3;
		bufferU[j++]=0;
	}
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
//****************** read ********************
	PrintMessage(strings[S_ReadEE]);		//read EEPROM ...
	for(i=0,j=1;i<dim;i+=DIMBUF-4){
		bufferU[j++]=SPI_READ;
		bufferU[j++]=i<dim-(DIMBUF-4)?DIMBUF-4:dim-i;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(4);
		read();
		if(bufferI[1]==SPI_READ&&bufferI[2]<0xFA){
			for(z=3;z<bufferI[2]+3&&z<DIMBUF;z++) memEE[k++]=bufferI[z];
		}
		PrintStatus(strings[S_CodeReading2],i*100/(dim),i);	//"Read: %d%%, addr. %05X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log7],i,i,k,k);	//"i=%d(0x%X), k=%d(0x%X)\n"
			WriteLogIO();
		}
	}	
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
		memEE.SetSize(k);
	}
	else PrintMessage(strings[S_Compl]);
//****************** exit ********************
	bufferU[j++]=EXT_PORT;
	bufferU[j++]=0;
	bufferU[j++]=0;
	bufferU[j++]=EN_VPP_VCC;		//0
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	DisplayEE();	//visualize
	PrintMessage1(strings[S_End],(stop-start)/1000.0);	//"\r\nEnd (%.2f s)\r\n"
	if(saveLog) CloseLogFile();
}

void COpenProgDlg::Write25xx(int dim,int page=16,float wait=5.0)
// write SPI memories
// dim=size in bytes
// page=page size		wait=write delay
{
	CString str;
	int sizeEE=memEE.GetSize();
	hvreg=0;
	int k=0,z=0,i,j;
	int err=0;
	if(dim>0x1000000||dim<0){
		PrintMessage(strings[S_EELim]);	//"EEPROM size out of limits\r\n"
		return;
	}
	if(saveLog){
		OpenLogFile();	//"Log.txt"
		fprintf(logfile,"Write25xx(%d,%d,%f)    (0x%X)\n",dim,page,wait,dim);
	}
	if(dim>sizeEE){
		i=sizeEE;
		memEE.SetSize(dim);
		for(;i<dim;i++) memEE[i]=0xFF;
		sizeEE=dim;
	}
	if(dim<1){
		PrintMessage(strings[S_NoCode]);	//"Data area is empty\r\n"
		return;
	}
	unsigned int start=GetTickCount();
	bufferU[0]=0;
	j=1;
	bufferU[j++]=VREG_DIS;
	bufferU[j++]=SPI_INIT;
	bufferU[j++]=2;				//0=100k, 1=200k, 2=300k
	bufferU[j++]=EN_VPP_VCC;		//VDD
	bufferU[j++]=0x1;
	bufferU[j++]=EXT_PORT;	//CS=1, HLD=1, WP=1
	bufferU[j++]=CS+HLD;
	bufferU[j++]=WP;
	bufferU[j++]=EXT_PORT;	//CS=0, HLD=1, WP=1
	bufferU[j++]=HLD;
	bufferU[j++]=WP;
	bufferU[j++]=SPI_WRITE;		//WRITE STATUS
	bufferU[j++]=2;
	bufferU[j++]=1;
	bufferU[j++]=0;
	bufferU[j++]=EXT_PORT;	//CS=1, HLD=1, WP=1
	bufferU[j++]=CS+HLD;
	bufferU[j++]=WP;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(wait+1);
	read();
	if(saveLog)WriteLogIO();
//****************** write ********************
	PrintMessage(strings[S_EEAreaW]);	//"Write EEPROM ... "
	for(;page>=DIMBUF-22;page>>=1);
	//page=1;
	for(i=0,j=1;i<dim;i+=page){
		bufferU[j++]=EXT_PORT;	//CS=0, HLD=1, WP=1
		bufferU[j++]=HLD;
		bufferU[j++]=WP;
		bufferU[j++]=SPI_WRITE;		//WRITE ENABLE
		bufferU[j++]=1;
		bufferU[j++]=6;
		bufferU[j++]=EXT_PORT;	//CS=1, HLD=1, WP=1
		bufferU[j++]=CS+HLD;
		bufferU[j++]=WP;/**/
		bufferU[j++]=EXT_PORT;	//CS=0, HLD=1, WP=1
		bufferU[j++]=HLD;
		bufferU[j++]=WP;
		bufferU[j++]=SPI_WRITE;		//WRITE
		if(dim>0x10000){				//24 bit address
			bufferU[j++]=4+page;
			bufferU[j++]=2;
			bufferU[j++]=i>>16;
			bufferU[j++]=(i>>8)&0xFF;
			bufferU[j++]=i&0xFF;
		}
		else if(dim>0x200){				//16 bit address
			bufferU[j++]=3+page;
			bufferU[j++]=2;
			bufferU[j++]=i>>8;
			bufferU[j++]=i&0xFF;
		}
		else{						//8 bit address
			bufferU[j++]=2+page;
			bufferU[j++]=2+(i&0x100?8:0);
			bufferU[j++]=i&0xFF;
		}
		for(k=0;k<page;k++) bufferU[j++]=memEE[i+k];
		bufferU[j++]=EXT_PORT;	//CS=1, HLD=1, WP=1
		bufferU[j++]=CS+HLD;
		bufferU[j++]=WP;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(wait+2);
		read();
		if(bufferI[2]!=SPI_WRITE||bufferI[3]>=0xFA) i=dim+10;
		PrintStatus(strings[S_CodeWriting2],i*100/(dim),i);	//"Write: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log7],i,i,0,0);	//"i=%d(0x%X), k=%d(0x%X)\n"
			WriteLogIO();
		}
	}
	PrintMessage(strings[S_Compl]);	//"completed\r\n"
//****************** verify EEPROM ********************
	PrintMessage(strings[S_EEV]);	//"Verify EEPROM ... "
	j=1;
	bufferU[j++]=EXT_PORT;	//CS=0, HLD=1, WP=0
	bufferU[j++]=HLD;
	bufferU[j++]=0;
	bufferU[j++]=SPI_WRITE;		//Read
	if(dim>0x10000){				//24 bit address
		bufferU[j++]=4;
		bufferU[j++]=3;
		bufferU[j++]=0;
		bufferU[j++]=0;
		bufferU[j++]=0;
	}
	else if(dim>0x200){				//16 bit address
		bufferU[j++]=3;
		bufferU[j++]=3;
		bufferU[j++]=0;
		bufferU[j++]=0;
	}
	else{						//8 bit address
		bufferU[j++]=2;
		bufferU[j++]=3;
		bufferU[j++]=0;
	}
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	if(saveLog)WriteLogIO();
	k=0;
	for(i=0,j=1;i<dim;i+=DIMBUF-4){
		bufferU[j++]=SPI_READ;
		bufferU[j++]=i<dim-(DIMBUF-4)?DIMBUF-4:dim-i;
		bufferU[j++]=FLUSH;
		for(;j<DIMBUF;j++) bufferU[j]=0x0;
		write();
		msDelay(4);
		read();
		if(bufferI[1]==SPI_READ&&bufferI[2]<0xFA){
			for(z=3;z<bufferI[2]+3&&z<DIMBUF;z++){
				if(memEE[k++]!=bufferI[z]){
					PrintMessage("\r\n");
					PrintMessage4(strings[S_CodeVError],i+z-3,i+z-3,memEE[k-1],bufferI[z]);	//"Errore in verifica, indirizzo %04X (%d), scritto %02X, letto %02X\r\n"
					err++;
				}
			}
		}
		PrintStatus(strings[S_CodeV2],i*100/(dim),i);	//"Verify: %d%%, addr. %04X"
		j=1;
		if(saveLog){
			fprintf(logfile,strings[S_Log8],i,i,k,k,err);	//"i=%d, k=%d, err=%d\n"
			WriteLogIO();
		}
		if(err>=max_err) break;
	}
	if(k!=dim){
		PrintMessage("\r\n");
		PrintMessage2(strings[S_ReadEEErr],dim,k);	//"Error reading EEPROM area, requested %d bytes, read %d\r\n"
		memEE.SetSize(k);
	}
	PrintMessage1(strings[S_ComplErr],err);	//"completed: %d errors\r\n"
//****************** exit ********************
	bufferU[j++]=EN_VPP_VCC;
	bufferU[j++]=0x0;
	bufferU[j++]=FLUSH;
	for(;j<DIMBUF;j++) bufferU[j]=0x0;
	write();
	msDelay(2);
	read();
	unsigned int stop=GetTickCount();
	StatusBar.SetWindowText("");
	PrintMessage3(strings[S_EndErr],(stop-start)/1000.0,err,err!=1?strings[S_ErrPlur]:strings[S_ErrSing]);	//"\r\nEnd (%.2f s) %d %s\r\n\r\n"
	if(saveLog) CloseLogFile();
}
