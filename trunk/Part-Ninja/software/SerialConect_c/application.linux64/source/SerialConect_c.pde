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
float[] cordX=new float[3];
float[] cordY=new float[3];
float[] corddX=new float[3];
float[] corddY=new float[3];

float cx1,cy1,cx2,cy2,cx3,cy3,dx1,dx2,dx3,dy1,dy2,dy3;
RectButton testButton;
RectButton clipButton;

int testF=0,clipF=0;
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
  //size(140, (Serial.list().length*25)+40);
  size(600,250);
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
   while(nSend==0)
    {
      myPort.clear();
      buttoncolor = color(102);
      highlight = color(51); 
      testButton = new RectButton(50, 200, 25, buttoncolor, highlight,"Test");
      clipButton = new RectButton(200, 200, 25, buttoncolor, highlight,"ClipB");
      testButton.display();
      clipButton.display();
      myPort.write('s');
      while(myPort.available()==0);
      rB = (char)myPort.read();
      print(rB);
      if(rB=='s')
      {
        nSend++;
        background(153);
        stroke(0);
        strokeWeight(3);
      }
    }
    testButton.update();
    clipButton.update();
    testButton.display();
    clipButton.display();
    if(testF!=0)
    {
      while(nSend2==0)
      { 
        //myPort.clear(); 
        myPort.write('p');
        while(myPort.available()==0);
        rB=(char)myPort.read();
        print(rB);
        if(rB=='p')nSend2++;
      }
      background(153); 
      nSend2=0;
      drawDisplay();


      while(myPort.available()<7);
      nC=myPort.read();
      print(nC);
      diff=myPort.read();
      print(diff);
      pP=myPort.read();
      print(pP);
      pPartSS = PartType[pP];
      pP=myPort.read();
      PartSS=PartType[pP];
      pin1=(char)myPort.read();
      pin2=(char)myPort.read();
      pin3=(char)myPort.read();
      if(nC>0)
      {
        int vv=nC*2+2;
        while(myPort.available()<vv);
        for(int pi=0;pi<nC;pi++)
        {
          tList[pi][0]=myPort.read();
          tList[pi][1]=myPort.read();
          if(pi>(diff-1))drawCP(cordX[tList[pi][0]],cordY[tList[pi][0]],cordX[tList[pi][1]],cordY[tList[pi][1]]);
          else drawCP(corddX[tList[pi][0]],corddY[tList[pi][0]],corddX[tList[pi][1]],corddY[tList[pi][1]]);
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
        textFont(font,12);
        text(s,400,20);
        testF=0;
    }
        if(clipF!=0)
        {
          clipF=0;
          cp.copyString(s);
        }
        myPort.clear();
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
            ComPorts[selected].basecolor =color(0,255,0);
            ComPorts[selected].highlightcolor =color(0,255,0);
            ComPorts[selected].update();
            ComPorts[selected].display();
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
    if( overRect(x, y, 4*size, size) ) {
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
    textFont(font,25);
    text(sBtext,x+10,y+size-2);
  }
}

void drawDisplay()
{
  fill(255);
  rect(10,10,350,150);
  textFont(font,12);
  cordX[0]=cx1=100;
  cordY[0]=cy1=25;
  cordX[1]=cx2=50;
  cordY[1]=cordY[2]=cy2=cy3=100;
  cordX[2]=cx3=150;
  corddX[0]=dx1=cx1+150;
  corddX[1]=dx2=cx2+150;
  corddX[2]=dx3=cx3+150;
  corddY[0]=dy1=cy1;
  corddY[1]=dy2=cy2;
  corddY[2]=dy3=cy3;
  fill(0);
  ellipse(cx1, cy1, 5, 5);

  text('1',cx1-5,cy1-5);
  stroke(0);
  strokeWeight(3);
  ellipse(cx2, cy2, 5, 5);
  text('2',cx2-5,cy2+15);
  ellipse(cx3, cy3, 5, 5);
  text('3',cx3-5,cy3+15);
  text("LOW",cx2+35,cy2+30);
  ellipse(dx1, dy1, 5, 5);
  fill(0);
  text('1',dx1-5,cy1-5);
  ellipse(dx2, cy2, 5, 5);
  text('2',dx2-5,cy2+15);
  ellipse(dx3, dy3, 5, 5);
  text('3',dx3-5,dy3+15);
  text("HIGH",dx2+33,dy2+30);
  
}

void drawCP(float x1, float y1,float x2, float y2)
{
  float x3,y3,K,k,j,x4,y4,x5,y5,ky,kx,tx,ty;
  j=5;
  k=y2-y1;
  if(x2==x1)
  {
    kx=1;
    ky=0;
  }
  else 
  {
    k=k/(x2-x1);
    print(k);
    k=atan(k);
    print(k);
    kx=sin(k);
    ky=cos(k);
    print(kx);
    print(ky);
  }
  K=0.8;
  y3=((y2-y1)*K)+y1;
  x3=((x2-x1)*K)+x1;
  K=0.1;
  ty=((y2-y1)*K)+y1;
  tx=((x2-x1)*K)+x1;   
  x4=x3+(kx*j);
  x5=x3-(kx*j);
  y4=y3-(ky*j);
  y5=y3+(ky*j);
  stroke(0);
  strokeWeight(3);
  line(tx,ty,x3,y3);
  K=0.9;
  y3=((y2-y1)*K)+y1;
  x3=((x2-x1)*K)+x1; 
  triangle(x3, y3, x4, y4, x5, y5);
}

void mousePressed() 
{
  if((mouseY>200)&&(mouseY<225))
  {
    if((mouseX>50)&&(mouseX<150))testF=1;
    if((mouseX>200)&&(mouseX<300))clipF=1;
  }
}
