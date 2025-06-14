#include "CytronMotorDriver.h"

// Configure the motor driver.
CytronMD motor(PWM_DIR, 11, 12);  // PWM = Pin 3, DIR = Pin 4.
#define minPin       23 //Limit Switch 1
#define maxPin        25 // Limit Switch 2
#define M0  36 //correct
#define M1  34 //correct
#define M2  32 //correct
#define M3  30 // correct
#define M4  28 // correct

#define LED_ONBOARD 13

 
int RR = 15;
int sensorValue = 0;
unsigned int inTime = 1000;
unsigned int outTime = 2000;
//------------------------------
unsigned long t1, t2, t3; //
double itime, etime, rr;
//---------------------------------
int I[5] = {0, 1, 1, 1, 1};
int E[5] = {0, 4, 3, 2, 1};
int modePins[] = {M0, M1, M2, M3, M4};

int check = 0;

void setup() {
  Serial.begin(9600);
  pinMode(minPin, INPUT_PULLUP);
  pinMode(maxPin, INPUT_PULLUP);
  for(int a = 0; a <= 4; a++)
  {
    pinMode(modePins[a], INPUT);
  }
  delay(2000);
  Serial.println("Ventilator On");

  for(int x = 0; x <= 4; x++)
  {
    Serial.print("Checking Pin : ");
    Serial.print(modePins[x]);
    Serial.print(" --> ");
    Serial.println(digitalRead(modePins[x]));
    check += digitalRead(modePins[x]);
  }

  if(check > 1)
  {
    Serial.println("FATAL ERROR");
    Serial.println(check);
  }
}

void loop() {
  //Checking if the mode selector pins are all correctly connected


  //Reading a value of pin A0 for respiration rate (Variable resistor)
  sensorValue = analogRead(0);
  //Serial.println(sensorValue);
  RR = map(sensorValue, 0, 1023, 8, 30);  //Maps a value from A0 to be between 8-30

  //Reading the mode selector dial and putting the ventilator in the correct I:E mode
  for(int i = 0; i <= 4; i++)
  {
    if(digitalRead(modePins[0]) == 1)
    {
      motorStop();
      break;
    }
    else if(digitalRead(modePins[i]) == 1)
    {
      GetInExTime(RR, I[i], E[i]);
      motorRun();
      break;
    }
  }

  

}

void GetInExTime(int RR, int I, int E)
{
  inTime = 1000*(60/RR)*I/(I+E);
  outTime = 1000*(60/RR)*E/(I+E);
  
  Serial.print("Selector mode : ");
  Serial.print(I);
  Serial.print(":");
  Serial.println(E);
  Serial.print("Respiration rate : ");
  Serial.println(RR);
  Serial.print("Inspire time : ");
  Serial.println(inTime);
  Serial.print("Expire time : ");
  Serial.println(outTime);
  Serial.println("-----------------------");
}

void motorRun()
{
  while(digitalRead(minPin) == HIGH)
  {  t1 = millis();
    motor.setSpeed(255);
    motor.setSpeed(0);
  }
  delay(inTime);
  t2 = millis();
  while(digitalRead(maxPin) == HIGH)
  {
    motor.setSpeed(-255);
  motor.setSpeed(0);
  }
  delay(outTime);
   t3 = millis();

   itime = t2-t1;
    etime = t3-t2; 
    rr = 60000/(itime+etime);

    Serial.println("!! Output result!!");
    Serial.print("OUT I time: ");
    Serial.println(itime);
    Serial.print("OUT E time: ");
    Serial.println(etime);
    Serial.print("OUT RR: ");
    Serial.println(rr);
    Serial.println();
}

void motorStop()
{
  motor.setSpeed(-255);
  motor.setSpeed(0);
}
