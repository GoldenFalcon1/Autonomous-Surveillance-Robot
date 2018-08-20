#include <Ultrasonic.h>          
////include ultrasonic library

/////////Front Sensor
#define TRIGGER_PIN  8
#define ECHO_PIN     9

////////Left Sensor 1
#define TRIGGER_PIN1  8
#define ECHO_PIN1     10

//////////left Sensor 2
#define TRIGGER_PIN2  8
#define ECHO_PIN2     11

//////////Right Sensor 1
#define TRIGGER_PIN3  8
#define ECHO_PIN3     12

//////////Right Sensor 2
#define TRIGGER_PIN4  8
#define ECHO_PIN4     13


//////////Ultrsonic Configuration
long timeOut = 100000;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN, timeOut);

Ultrasonic ultrasonic1(TRIGGER_PIN1, ECHO_PIN1, timeOut);

Ultrasonic ultrasonic2(TRIGGER_PIN2, ECHO_PIN2, timeOut);

Ultrasonic ultrasonic3(TRIGGER_PIN3, ECHO_PIN3, timeOut);
Ultrasonic ultrasonic4(TRIGGER_PIN4, ECHO_PIN4, timeOut);

float cmMsec4,cmMsec3,cmMsec,cmMsec2,cmMsec1;             
  ////Declaration of variable to scope them to GLOBAL
  
 int limit =255;
void setup() {
   //Initialize baud rate for serial monitoring
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,INPUT);
   pinMode(10,INPUT);
    pinMode(11,INPUT);
     pinMode(12,INPUT);
      pinMode(13,INPUT);
  
  
}

void loop() {
 moveforward();
    ////Obstacle Checking accross all directions    
    
    checkleft1();
    checkright2();
while((cmMsec3 <= limit)&(cmMsec2 <=limit)){
  turnright(255);
  checkleft1();
  checkright2();
}
while(cmMsec3 <=limit) {
  turnright(0);
  checkleft1();
}
    
    checkleft2();
    checkright1();
while((cmMsec1 <= limit)&(cmMsec4 <=limit)) {
  turnleft(255);
  checkleft2();
  checkright1();
}
while(cmMsec1 <=limit){
  turnleft(0);
  checkright1();
}

    checkfront();
while(cmMsec <=limit){
  stop();
  checkfront();
}

}


 ////////Move forward function for the Robot   
void moveforward()
{
  //Motor Initialization
    int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 7;
int speedPinB = 6; // Needs to be a PWM pin to be able to control motor speed
 analogWrite(speedPinA, 255);
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, 255);
digitalWrite(dir1PinB, HIGH);
digitalWrite(dir2PinB, LOW);
}

////////////Function to Turn Left
void turnleft(int speed)
{
 //Motor Initialization
    int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 7;
int speedPinB = 6; // Needs to be a PWM pin to be able to control motor speed
 analogWrite(speedPinA, speed);
digitalWrite(dir1PinA, HIGH);
digitalWrite(dir2PinA, LOW);
analogWrite(speedPinB, 255);
digitalWrite(dir1PinB, HIGH);
digitalWrite(dir2PinB, LOW);
}
/// Funtion to Turn Right
void turnright(int speed)
{
 //Motor Initialization
    int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 7;
int speedPinB = 6; // Needs to be a PWM pin to be able to control motor speed
 analogWrite(speedPinA, 255);
digitalWrite(dir1PinA, LOW);
digitalWrite(dir2PinA, HIGH);
analogWrite(speedPinB, speed);
digitalWrite(dir1PinB, LOW);
digitalWrite(dir2PinB, HIGH);
}

// Function to stop the Robot
void stop()
{
 //Motor Initialization
    int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 5; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 7;
int speedPinB = 6; // Needs to be a PWM pin to be able to control motor speed
 analogWrite(speedPinA, 0);
digitalWrite(dir1PinA, 0);
digitalWrite(dir2PinA, 0);
analogWrite(speedPinB, 0);
digitalWrite(dir1PinB, 0);
digitalWrite(dir2PinB, 0);
  
}

///Check front distance using HC-SR04
void checkfront()
{


  cmMsec = ultrasonic.Ranging(CM);

  Serial.print("Sensor");
  Serial.print(", CM: ");
  Serial.println(cmMsec);

 }

///Check left front distance using HC-SR04 
 void checkleft1()
 {
  
  cmMsec3 = ultrasonic3.Ranging(CM);
 
  Serial.print("Sensor 3");
  Serial.print(", CM: ");
  Serial.println(cmMsec3);
 
 }
 ///Check left back distance using HC-SR04
 void checkleft2()
 {
  cmMsec4 = ultrasonic4.Ranging(CM);
 
  Serial.print("Sensor 4");
  Serial.print(", CM: ");
  Serial.println(cmMsec4);

 }
 
 ///Check Right front distance using HC-SR04
void checkright1()
 {
  cmMsec1 = ultrasonic1.Ranging(CM);
 
  Serial.print("Sensor 1");
  Serial.print(", CM: ");
  Serial.println(cmMsec1);

 }
 
  ///Check Right back distance using HC-SR04
 void checkright2()
 {
cmMsec2 = ultrasonic2.Ranging(CM);
  
  Serial.print("Sensor 2");
  Serial.print(", CM: ");
  Serial.println(cmMsec2);
  
 }



