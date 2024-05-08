#define anode 10
// ........................soil ............................
#define SOIL_CONTROL 0
#define SOIL_ADC A0
// ........................ultrasonic Sensor............................
#define TRIG 9
#define ECHO 8
#define pump 11
#define fan 12
// ........................LCD............................
#include <LiquidCrystal.h>
LiquidCrystal lcd (7,6,5,4,3,2);
// ........................ultrasonic Sensor............................
float duration, distanceCM;
void setup() {
  // ........................Temp Sensor............................
  pinMode(A4,INPUT);
  Serial.begin(9600);
  //........................ soil .................................
  pinMode(SOIL_ADC,INPUT);
  pinMode(SOIL_CONTROL,OUTPUT);
  digitalWrite(SOIL_CONTROL,LOW);
  // ........................LCD............................
  lcd.begin(16,2);
  lcd.clear();
  // ........................ULTRASONIC Sensor............................
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(anode,OUTPUT);
  pinMode(pump,OUTPUT);
  pinMode(fan,OUTPUT);
}


void loop() {
  Serial.println(ultraRead());
 lcd.clear();
 
 // ........................Temp Sensor............................
 lcd.setCursor(0,1);

lcd.print(LMread());
delay(100);

// ........................ soil Sensor............................
int soil = SoilMoistureSensor();
lcd.setCursor(0,0);
lcd.print("Moisture: " + String (soil));
delay(250);
// ........................ ultrasonic Sensor............................

//Serial.println(LMread());

if(ultraRead() < 50.0)
{
  TurnOnLCD();
   delay(3000);
}
else
{
  TurnOffLCD();
}

  if (SoilMoistureSensor()>=500)
  {
  digitalWrite(pump,LOW);
  }
  else
  {
    digitalWrite(pump,HIGH);
  }




  
if(LMread() >40)
  {
 digitalWrite(fan,LOW);
   }
else
  {
 digitalWrite(fan,HIGH);
   }
}





// ........................ Soil read function ............................
int SoilMoistureSensor() {
  digitalWrite(SOIL_CONTROL,HIGH);
  delay(25);
  int soil = analogRead(SOIL_ADC);
  delay(25);
  digitalWrite(SOIL_CONTROL,LOW);
  return soil;
}
// ........................ultrasonic function ............................
float ultraRead()
{
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  duration = pulseIn(ECHO,HIGH);
  distanceCM = duration*0.5*0.034;
  return distanceCM;
}
// ........................LM REad funtion Sensor............................
float LMread ()
{
  int adc = analogRead(A4);
float Vout = (adc / 1024.0)*5.0*1000.0;
Serial.println(adc);
float tempC = Vout /10.0;
return tempC;
}
// ........................turn the lcd on function............................
void TurnOnLCD()
{
 digitalWrite(anode,HIGH);
 lcd.display();
}
// ........................turn the lcd off function............................
void TurnOffLCD()
{
 digitalWrite(anode,LOW);
 lcd.noDisplay();
}

 
