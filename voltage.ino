int m;// initialise variable m
float n;//initialise variable n
void setup()
{
  pinMode(A2,INPUT); // set pin a0 as input pin
  Serial.begin(9600);// begin serial communication between arduino and pc
}
void loop()
{
  m=analogRead(A2);// read analog values from pin A0 across capacitor
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
}
