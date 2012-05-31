/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */

import java.awt.datatransfer.*;
import processing.serial.*;


String[] PartType = {"ERROR","NFET","PFET","NMOS","PMOS","NPN","CA","PNP","CC",
	"DIODE","TRIAC","SCR","CAP","RES","ZENER","DD","","","","","","","NOID",
"ERROR1","ERROR2","ERROR3","ERROR4","ERROR5"};

ClipHelper cp = new ClipHelper();
Serial myPort;  // Create object from Serial class



PFont font;
boolean locked = false;
color buttoncolor = color(204);
color highlight = color(153);
RectButton[] ComPorts = new RectButton[Serial.list().length];
int selected;
int startF;


int SerEF=0;
int val;      // Data received from the serial port
int nSend=0,nSend2=0;
int temp;
int pP;
int nC=0,diff,high,low,test;
char pin1,pin2,pin3;
char rB;
String PartSS,pPartSS;
String[] sSerial = Serial.list();
int[][] tList=new int[12][3];
String s;
void setup()
{
  size(140, (Serial.list().length*25)+40);
  
  font = loadFont("Arial-Black-48.vlw"); 
  textFont(font,25);
  for (int i=0;i<sSerial.length;i++)
  {
    buttoncolor = color(102);
    highlight = color(51); 
    ComPorts[i] = new RectButton(20, 20+(i*30), 25, buttoncolor, highlight,sSerial[i]); 
    ComPorts[i].display();
  } 
  
  //myPort = new Serial(this, "COM9", 115200);
}


void draw()
{
  if(startF==1)
  {
    test=0;
    ComPorts[selected].basecolor =color(0,255,0);
    ComPorts[selected].highlightcolor =color(0,255,0);
    ComPorts[selected].update();
    ComPorts[selected].display();
    
    while(nSend==0)
    {
      myPort.write('s');
      while(SerEF ==0);
      SerEF =0;
      rB = (char)myPort.read();
      if(rB=='s')nSend++;
    }
    while(nSend2==0)
    {
      myPort.write('p');
      while(SerEF ==0);
      SerEF =0;
      rB = (char)myPort.read();
      if(rB=='p')nSend2++;
    }
    nSend2=0;  
    if ( myPort.available() > 0) 
    {  // If data is available,
      test = myPort.read();
      if(test=='D')
      {
        test = myPort.read();
        if(test=='P')
        {
          //print("\n\n");
          nC=myPort.read();
          diff=myPort.read();
          pP=myPort.read();
          pPartSS = PartType[pP];
          pP=myPort.read();
          PartSS=PartType[pP];
          pin1=(char)myPort.read();
          pin2=(char)myPort.read();
          pin3=(char)myPort.read();
          if(nC>0)
          {
            for(int pi=0;pi<nC;pi++)
            {
              tList[pi][0]=myPort.read();
              tList[pi][1]=myPort.read();
              high = myPort.read();
              low = myPort.read();
              tList[pi][2]=high<<8;
              tList[pi][2]=tList[pi][2]|low;
            }
            high = myPort.read();
            low = myPort.read();
            temp = high<<8;
            temp = temp|low;
          }
  
      
        s="";
        s+="nC: " + nC +'\n';
        s+="diff: " + diff +'\n';
        s+="pPartSS: " + pPartSS +'\n';
        s+="PartSS: " + PartSS +'\n';
        s+="Pin1: " + pin1+" PIN2: " + pin2 +" PIN3: " + pin3 + '\n';   
        if(nC>0)
        {
          for(int i=0;i<nC;i++)
          {
            //print("CP"+i+": " + tList[i][0] + "->" + tList[i][1]+"   testVal: " + tList[i][2]+'\n');
            s+="CP"+(i+1)+": " + (tList[i][0]+1) + "->" + (tList[i][1]+1)+"   testVal: " + tList[i][2]+'\n';
          }
          s+="partVal: " + temp +'\n';
          //print ("partVal: " + temp +'\n');
        }
        println(s);
        cp.copyString(s);
      }

      }
    }
  }
  else
  {
    if(mousePressed)
    {
      int x,y;
      print("\n"+mouseX+"  "+mouseY);

      x=mouseX;
      y=mouseY;
      if((x>20&&x<120))
      {
        for(int j=0;j<Serial.list().length;j++)
        {
          if(mouseY>((j*30)+20)&&mouseY<((j*30)+45))
          {
            myPort = new Serial(this, Serial.list()[j], 115200);
            startF=1;
            selected = j;
          }
        }
      }
      
    }
  }

}




// //////////////////
// Clipboard class for Processing
// by seltar  
// v 0115
// only works with programs. applets require signing

class ClipHelper
{
 Clipboard clipboard;
 ClipHelper()
 {
   getClipboard();  
 }
 
 void getClipboard ()
 {
   // this is our simple thread that grabs the clipboard
   Thread clipThread = new Thread() {
public void run() {
  clipboard = getToolkit().getSystemClipboard();
}
   };

   // start the thread as a daemon thread and wait for it to die
   if (clipboard == null) {
try {
  clipThread.setDaemon(true);
  clipThread.start();
  clipThread.join();
}  
catch (Exception e) {
}
   }
 }

 void copyString (String data)
 {
   copyTransferableObject(new StringSelection(data));
 }

 void copyTransferableObject (Transferable contents)
 {
   getClipboard();
   clipboard.setContents(contents, null);
 }

 String pasteString ()
 {
   String data = null;
   try {
data = (String)pasteObject(DataFlavor.stringFlavor);
   }  
   catch (Exception e) {
System.err.println("Error getting String from clipboard: " + e);
   }

   return data;
 }

 Object pasteObject (DataFlavor flavor)  
   throws UnsupportedFlavorException, IOException
 {
   Object obj = null;
   getClipboard();

   Transferable content = clipboard.getContents(null);
   if (content != null)
obj = content.getTransferData(flavor);

   return obj;
 }
}

	

void serialEvent(Serial myPort) 
{
  SerEF=1;
}

class Button
{
  int x, y;
  int size;
  String sBtext;
  color basecolor, highlightcolor;
  color currentcolor;
  boolean over = false;
  boolean pressed = false;   

  void update() 
  {
    if(over()) {
      currentcolor = highlightcolor;
    } 
    else {
      currentcolor = basecolor;
    }
  }

  boolean pressed() 
  {
    if(over) {
      locked = true;
      return true;
    } 
    else {
      locked = false;
      return false;
    }    
  }

  boolean over() 
  { 
    return true; 
  }

  boolean overRect(int x, int y, int width, int height) 
  {
    if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
      return true;
    } 
    else {
      return false;
    }
  }

  boolean overCircle(int x, int y, int diameter) 
  {
    float disX = x - mouseX;
    float disY = y - mouseY;
    if(sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
      return true;
    } 
    else {
      return false;
    }
  }

}

class RectButton extends Button
{
  RectButton(int ix, int iy, int isize, color icolor, color ihighlight, String itext) 
  {
    x = ix;
    y = iy;
    sBtext=itext;
    size = isize;
    basecolor = icolor;
    highlightcolor = ihighlight;
    currentcolor = basecolor;
  }

  boolean over() 
  {
    if( overRect(x, y, size, size) ) {
      over = true;
      return true;
    } 
    else {
      over = false;
      return false;
    }
  }

  void display() 
  {
    stroke(255);
    fill(currentcolor);
    rect(x, y, 4*size, size);
    fill(255,0,0);
    text(sBtext,x+10,y+size-2);
  }
}

