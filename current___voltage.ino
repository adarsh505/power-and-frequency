#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int sensorIn = A5;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module


double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
int m;// initialise variable m
float n;//initialise variable n



void setup(){ 
  pinMode(A0,INPUT); 
 Serial.begin(9600);
   lcd.begin(16, 2);
lcd.clear();
}

void loop(){
 
 m=analogRead(A0);// read analog values from pin A0 across capacitor
   n=(m* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
  
   Serial.print("   analaog input  " ) ; // specify name to the corresponding value to be printed
   Serial.print(m) ; // print input analog value on serial monitor
   if (n < 5 )
   Serial.print("   ac voltage = 0 v  ") ; // specify name to the corresponding value to be printed
   if (n > 170  )
   Serial.print("   ac voltage = 223 v  ") ; // specify name to the corresponding value to be printed
    if (n < 110 && n > 10 )
   Serial.print("   ac voltage = 101 v ") ; // specify name to the corresponding value to be printed
   Serial.println();
   delay(5000);
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
   lcd.setCursor(0, 1);
     lcd.print("current = " );
          lcd.print(AmpsRMS);
     



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
