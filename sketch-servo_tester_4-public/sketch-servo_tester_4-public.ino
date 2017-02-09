/*************************************************/
//Arduino Servo Tester sketch Version 1.4
// Using a single switch to select between 3 modes
// Written by Pason Tanpaiboon January 2016
/*************************************************/
/*
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
*/

#include <Servo.h>
Servo myservo;  

const int ledPinOne = 2; // Manual mode
const int ledPinTwo = 4; // Nutral mode
const int ledPinThree = 6; // Auto mode
const int modePin = 9; // Toggle push button
const int servoValu = 10; // servo signal output

int mode = 0; // Selector State (Initial state = ALL OFF)
int val = 0; // Pin 9 HIGH/LOW Status
int potpin = 0; //set input potentiometer signal (A0)
int butState = 0; // Last Button State
int lastMode = 0; // Last Mode State

int pos = 0;    // value to store the servo position
int servoVal =0;
int potVal;     // read value from potentiometer

void setup () 
{
  Serial.begin(9600);
  pinMode(ledPinOne, OUTPUT);
  pinMode(ledPinTwo, OUTPUT);
  pinMode(ledPinThree, OUTPUT);
  pinMode(modePin, INPUT);
  pinMode(servoVal, INPUT);
  myservo.attach(10);  // attached servo on pin 10
 }

void loop() 
{
  val = digitalRead(modePin);//Toggle push button activate (Long push for mode3)
  if ( lastMode==3 && val==HIGH ){
    mode=0;
  }
  if (val != butState && val == HIGH){
    mode++;
  }
  if (mode>3 || mode<=0){
    mode=1; //restart mode 1
  }
  butState = val; // newest button state trace
 /*****************************Manual mode***********************************/
  if ( mode==1 && val==LOW ){
    lastMode=mode;//remember last mode
    digitalWrite(ledPinThree, LOW);
    delay(15);
    digitalWrite(ledPinOne, HIGH);
    potVal = analogRead(potpin);  
    potVal = map(potVal, 0, 1023, 0, 180);  
    myservo.write(potVal);  
    delay(15);  
    Serial.print("manual mode");
    Serial.print("  potVal : ");
    Serial.println(potVal);
  }
/******************************Nutral mode*************************************/
  if ( mode==2 && val==LOW ){
    lastMode=mode;//remember last mode
    digitalWrite(ledPinOne, LOW);
    delay(15);
    digitalWrite(ledPinTwo, HIGH);
    myservo.write(90);// tell servo to go to position in variable 'pos'
    Serial.println(" nutral mode ");   
  }
  /*****************************Auto mode***************************************/
  if ( mode==3 && val!=1 ){
    digitalWrite(ledPinTwo, LOW);
    delay(15);
    digitalWrite(ledPinThree, HIGH);
    Serial.println("--auto mode-- ");
      lastMode=mode;//remember last mode
      if( mode==3 && butState==LOW ){
      Serial.println("auto positive ");
      for (pos = 0; pos < 180; pos += 1) { 
      myservo.write(pos);             
      delay(15);                      
      }
      Serial.println("auto negative ");
      for (pos = 180; pos > 0; pos -= 1) { 
      myservo.write(pos);              
      delay(15);                      
      }
    }
  }
}










