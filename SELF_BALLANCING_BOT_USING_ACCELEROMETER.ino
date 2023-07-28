//Quick accelerometer test
//X is on A0; Y is on A1; Z is on A2
 
//Analog input pins 0, 1, and 2
//are what I send the x,y, and z
//accelerometer outputs to, respectively
int xAxisPin = A5;
int yAxisPin = A4;
int zAxisPin = A3;
 
//Variables to hold the returned
//ADC data from the analog input
//pins
int xAxisValADC = 0;
int yAxisValADC = 0;
int zAxisValADC = 0;
 
//Variables to hold the voltage
//values after converting from ADC
//units to mV
float xAxisValmV = 0;
float yAxisValmV = 0;
float zAxisValmV = 0;
 
//My Arduino Uno has a 10-bit
//AD converter, with a max value
//of 1023
int ADCMaxVal = 1023;
 
//The AD converter voltage
//is powered by 5V
float mVMaxVal = 5000;
 
//I measured the power going to the
//accelerometer as actually being 
//3230 mV, so I use this value to 
//define the mid-point
float supplyMidPointmV = 3230 / 2;
 
//Since the supply is actually 3230
//mV, I know the output will be 323mV
//per 1g detected
int mVperg = 323;
 
//Multiply any acquired ADC value
//by mVPerADC to convert to mV
float mVPerADC = mVMaxVal / ADCMaxVal;
const int lmn = 2;
const int lmp = 3;
const int rmn = 4;
const int rmp = 5;
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 9, 8, 7, 6); 
byte customChar[8] = {
  0b10101,
  0b01010,
  0b10101,
  0b01010,
  0b10101,
  0b01010,
  0b10101,
  0b01010
};
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!"); 
  //I don't know if setting them to
  //input is necessary, but I do it
  //anyways.
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  lcd.createChar(4, customChar);  
  
}
 
void loop()
{
 for (int x = 0;x < 17;x++)
  {
  lcd.setCursor(x, 1);
  lcd.write(byte(4));
  delay(200);
  }
  //Read the x, y, and z values from
  //the analog input pins
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  xAxisValADC = analogRead(xAxisPin);
  yAxisValADC = analogRead(yAxisPin);
  zAxisValADC = analogRead(zAxisPin);
   
  //Convert the ADC values to millivolts
  xAxisValmV = xAxisValADC * mVPerADC;
  yAxisValmV = yAxisValADC * mVPerADC;
  zAxisValmV = zAxisValADC * mVPerADC;
  float a = (xAxisValmV - supplyMidPointmV) / mVperg;
  float b = (yAxisValmV - supplyMidPointmV) / mVperg;
  float c = (zAxisValmV - supplyMidPointmV) / mVperg;
  //This could be prettier. What's happening is the mid-point
  //voltage value is subtracted from the voltage recorded
  //from the analog input, and then that value is divided
  //by how many millivolts per g the accelerometer is
  //ouputing. This results in the value being printed
  //in units of g.
  /*
  Serial.print((xAxisValmV - supplyMidPointmV) / mVperg);
  Serial.print("\t");
  Serial.print((yAxisValmV - supplyMidPointmV) / mVperg);
  Serial.print("\t");
  Serial.print((zAxisValmV - supplyMidPointmV) / mVperg);
  Serial.print("\t");   
  Serial.println();
  */
  /*
   Serial.print(a);
   Serial.print("    ");
   Serial.print(b);
   Serial.print("    ");
   Serial.print(c);
   Serial.print("    ");      
   Serial.println("    ");
   delay(100);
  */
if( b < 0.30 && b > -0.10 )
{
  Serial.println("THE BOT IS STABLE");
  //bot is stable 
  //do nothing 
  lcd.print("STRAIGHT !!");
}

if( b > 0.30  )
{
  Serial.println("THE BOT IS TILTING RIGHT");
  lcd.print("TILTING RIGHT !!");
  //bot leaning forward 
  //wheels clock-wise  
  digitalWrite(lmn,LOW);
  analogWrite(lmp,70);
  digitalWrite(rmn,LOW);
  analogWrite(rmp,70);
}

if( b < -0.10 )
{
  Serial.println("THE BOT IS TILTING LEFT");
  lcd.print("TILTING LEFT !!");
  //bot leaning backwards
  //wheels anti-clockwise
  digitalWrite(lmn,HIGH);
  analogWrite(lmp,185);
  digitalWrite(rmn,HIGH);
  analogWrite(rmp,185);
}

}
