/**
 * Simple Read
 * 
 * Read data from the serial port and change the color of a rectangle
 * when a switch connected to a Wiring or Arduino board is pressed and released.
 * This example works with the Wiring / Arduino program that follows below.
 */

import java.awt.datatransfer.*;
import processing.serial.*;



ClipHelper cp = new ClipHelper();
Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
int nSend=0;
int temp;
int nC=0,diff,high,low,PartSS,pPartSS,test;
int[][] tList=new int[12][3];
String s;
void setup()
{
  size(200, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  //String portName = Serial.list()[0];
  myPort = new Serial(this, "COM9", 115200);
}

/*void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.read();         // read it and store it in val
  }
  background(255);             // Set background to white
  if (val == 0) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } 
  else {                       // If the serial value is not 0,
    fill(204);                 // set fill to light gray
  }
  rect(50, 50, 100, 100);
}
*/
void draw()
{
  test=0;  
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
        pPartSS=myPort.read();
        PartSS=myPort.read();
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
      
          
      /*print("nC: " + nC +'\n');
      print("diff: " + diff +'\n');
      print("pPartSS: " + pPartSS +'\n');
      print("PartSS: " + PartSS +'\n');*/  
      
      s="";
      s+="nC: " + nC +'\n';
      s+="diff: " + diff +'\n';
      s+="pPartSS: " + pPartSS +'\n';
      s+="PartSS: " + PartSS +'\n';
          
      if(nC>0)
      {
        for(int i=0;i<nC;i++)
        {
          //print("CP"+i+": " + tList[i][0] + "->" + tList[i][1]+"   testVal: " + tList[i][2]+'\n');
          s+="CP"+i+": " + tList[i][0] + "->" + tList[i][1]+"   testVal: " + tList[i][2]+'\n';
        }
        s+="partVal: " + temp +'\n';
        //print ("partVal: " + temp +'\n');
      }
      println(s);
      cp.copyString(s);
    }

    }
  }
  if(nSend==0)
    {
      myPort.write('a');
      nSend++;
    } 
            // Set background to white

}


/*

// Wiring / Arduino Code
// Code for sensing a switch status and writing the value to the serial port.

int switchPin = 4;                       // Switch connected to pin 4

void setup() {
  pinMode(switchPin, INPUT);             // Set pin 0 as an input
  Serial.begin(9600);                    // Start serial communication at 9600 bps
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {  // If switch is ON,
    Serial.print(1, BYTE);               // send 1 to Processing
  } else {                               // If the switch is not ON,
    Serial.print(0, BYTE);               // send 0 to Processing
  }
  delay(100);                            // Wait 100 milliseconds
}

*/

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
