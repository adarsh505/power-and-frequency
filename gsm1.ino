#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
float n1;  

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

}


void loop()
{
      SendMessage();
  delay(5000);
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918921235941\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("there is a short circuit fault on y phase");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
 
}
