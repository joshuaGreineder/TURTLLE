//Designate pins for Drive Motors

/*
const int RightFrontMotor = 1;
const int RightBackMotor = 2;
const int LeftFrontMotor = 3;
const int LeftBackMotor = 4;
*/

const int leftServoPin = 1;               // servo pin for LEFT wheel
const int rightServoPin = 2;              // servo pin for RIGHT wheel

//Servo setup

#include <Servo.h>
Servo LeftDriveControl;
Servo RightDriveControl;

//Setup servo open and close positions for end effector
int OpenPos = 0;
int ClosePos = 180;



void setup() {
  


  //Designate pins
  LeftDriveControl.attach(leftServoPin);
  RightDriveControl.attach(rightServoPin);
  
}

void loop() {

  forwardFast(100);
  delay(5000);
  reverseFast(100);
  delay(5000);

}


//End effector movement

void OpenEndEffector(){

  //myservo.write(OpenPos); 
  
}

void CloseEndEffector(){

  //myservo.write(ClosePos); 
  
}

//Drive direction functions
// "-" Is where the motor's polarity is reversed




