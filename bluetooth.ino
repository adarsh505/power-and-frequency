/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino with HC-06/HC-05
  Bluetooth 2.0 Serial Port Profile (SPP) module
  to connect your project to Blynk.

  Note: This only works on Android! iOS does not support SPP :(
        You may need to pair the module with your smartphone
        via Bluetooth settings. Default pairing password is 1234

  Feel free to apply it to any other example. It's simple!

  NOTE: Bluetooth support is in beta!

 *************************************************************/

#define BLYNK_USE_DIRECT_CONNECT

#define BLYNK_PRINT Serial

#include <BlynkSimpleSerialBLE.h>

#include <SoftwareSerial.h>

SoftwareSerial SwSerial(10, 11); // RX, TX





// You should get Auth Token in the Blynk App.

// Go to the Project Settings (nut icon).

char auth[] = "1b080ff4384c450fbdcb1f2250723c5f";



SoftwareSerial SerialBLE(10, 11); // RX, TX
const int sensorIn = A5;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
int m;// initialise variable m
float n;//initialise variable n
float power = 0;         // power in watt              
float Wh =0 ;             // Energy in kWh
unsigned long last_time =0;
unsigned long current_time =0;
unsigned long interval = 100;
float bill_amount = 0;   // 30 day cost as present energy usage incl approx PF 
unsigned int energyTariff = 8.0; // Energy cost in INR per unit (kWh)


void setup()

{
  pinMode(A0,INPUT); 

  // Debug console

  Serial.begin(9600);



  SerialBLE.begin(9600);

  Blynk.begin(SerialBLE, auth);



  Serial.println("Waiting for connections...");

  
}
BLYNK_READ(V5) //Blynk app has something on V5
{
 
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS); 
 Blynk.virtualWrite(V5, AmpsRMS); //sending to Blynk
  delay(1000);
     
}

float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
}
BLYNK_READ(V4)
{
   m=analogRead(A0);// read analog values from pin A0 across capacitor
   n=(m* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
   if (n < 5 )
   {
   Blynk.virtualWrite(V4,0); //sending to Blynk
   Serial.print("   ac voltage = 0 v  ") ; // specify name to the corresponding value to be printed
    delay(1000);

   }
   if (n > 170  )
   {

   Blynk.virtualWrite(V4,223); //sending to Blynk
   Serial.print("   ac voltage = 223 v  ") ; // specify name to the corresponding value to be printed
   delay(1000);

   }
    if (n < 100 && n > 10 )
    {
    Blynk.virtualWrite(V4,110); //sending to Blynk
   Serial.print("   ac voltage = 101 v ") ; // specify name to the corresponding value to be printed
   delay(1000);
    }
  
  }
  
BLYNK_READ(V3)
  { 
    power= (AmpsRMS * 220) * .8; 
  last_time = current_time;
  current_time = millis();    
  Wh = Wh+  power *(( current_time -last_time) /3600000.0) ; // calculating energy in Watt-Hour
  bill_amount = Wh * (energyTariff/1000);
  Blynk.virtualWrite(V3, power); //sending to Blynk
  delay(1000);
     
    }





void loop()

{

  Blynk.run();

  // You can inject your own code or combine it with other sketches.

  // Check other examples on how to communicate with Blynk. Remember

  // to avoid delay() function!

}
