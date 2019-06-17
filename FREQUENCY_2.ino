int m;// initialise variable m
float a;//initialise variable n
int n;// initialise variable m
float b;//initialise variable n
volatile byte freqcount;
unsigned int frequency;
unsigned long timeold;
int frequency1;

void freq_fun()
{
  freqcount++;
}

void setup() {
 Serial.begin(9600);
 pinMode(A0,INPUT); // set pin a0 as input pin
  pinMode(A1,INPUT); // set pin a0 as input pin

 attachInterrupt(0, freq_fun, FALLING);
 freqcount = 0;
 frequency = 0;
 timeold = 0;

}

void loop() {
  delay(1000);
  detachInterrupt(0);
  frequency = 60*50/(millis() - timeold)*freqcount;
  timeold = millis();
  freqcount = 0;
  
  frequency1 = frequency/4;
  if (frequency1 < 55)
  {
  Serial.print("frequency:");
  Serial.println(frequency1);
  }
  attachInterrupt(0, freq_fun, FALLING);
   m=analogRead(A0);// read analog values from pin A0 across capacitor
a=(m* .304177* .69444);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
 if (a > 180)
 {
   Serial.print("R ac voltage  ") ; // specify name to the corresponding value to be printed
   Serial.print(a) ; // prints the ac value on Serial monitor
   
   Serial.println();
  // put your main code here, to run repeatedly:
  n=analogRead(A1);// read analog values from pin A0 across capacitor
b=(n* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
 if (b > 180)
 {
   Serial.print(" Y ac voltage  ") ; // specify name to the corresponding value to be printed
   Serial.print(b) ; // prints the ac value on Serial monitor
   
   Serial.println();
  // put your main code here, to run repeatedly:
 }
  
 }
}
