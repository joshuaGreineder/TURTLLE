
#include<SoftwareSerial.h>
//Servos
const int leftServo = 3;
const int rightServo = 4;
const int left_backward_fast = 1800; // CCW
const int left_backward_slow = 1750;
const int left_forward_slow = 1250;
const int left_stop = 1500; // Center position
const int left_forward_fast = 1000; // CW
const int right_backward_fast = 1825; // CW
const int right_forward_slow = 1250;
const int right_stop = 1500; // Center position
const int right_forward_fast = 1000;
const int right_backward_slow = 1750;// CCW

//For Camera
const int RightPin = 6;
const int LeftPin = 7;
const int CenterPin = 8;



//Sensor
const int BLSharpIR = A8;
const int BRSharpIR = A7;
const int TRSharpIR = A6;
const int TLSharpIR = A5;
int BLVal = 0;
int BRVal = 0;
int TRVal = 0;
int TLVal = 0;

//BSA constants
const int buttonPin = 5;         // the number of the pushbutton pin
const int ledPin = LED_BUILTIN;  // the number of the LED pin
const int driverPUL = 0;
const int driverDIR = 1;
int pulseDelay = 1000;
bool setDir = HIGH;
int limitSwitch = 5;

//BSA variables will change:
//int buttonState = 0;

//Radio delay
const int Radio5Delay = 11;
const int Radio30Delay = 12;

//winch relay
int Relay = 10; //Where device is connected on-board

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftServo, OUTPUT);
  pinMode(rightServo, OUTPUT);

  //winch relay
  pinMode(Relay, OUTPUT); //Set the pin direction to output

  //For Camera
  pinMode(RightPin, INPUT);
  pinMode(LeftPin, INPUT);
  pinMode(CenterPin, INPUT);

  //radio delay
  pinMode(Radio5Delay, INPUT);
  pinMode(Radio30Delay, INPUT);

  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
  pinMode(5, INPUT);
}
void loop() {
  CheckForDelay();
  BLVal = analogRead(BLSharpIR);
  BRVal = analogRead(BLSharpIR);
  driveForward();
  if (BLVal > 490) turnRight();
}

void CheckForDelay() {
  if (Radio5Delay == HIGH) {
    Serial.println("5 second delay");
    servoMove(leftServo, left_stop);
    servoMove(rightServo, right_stop);
    delay(6000);
  }
  if (Radio30Delay == HIGH) {
    Serial.println("30 second delay");
    servoMove(leftServo, left_stop);
    servoMove(rightServo, right_stop);
    delay(35000);
  }
}

void correctLeft() {
  for (int x = 0 ; x < 2 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_fast);
    servoMove(rightServo, right_forward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}

void correctRight() {
  for (int x = 0 ; x < 2 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}

void driveForward() { // This is a subroutine for forward
  //for (int x = 0 ; x < 5 ; x++) { //This is a For-Loop see page 285 Vol 1
  servoMove(leftServo, left_forward_slow);
  servoMove(rightServo, right_forward_slow);
  delay(20); // This value changes speed of motor, do not set < 20ms
  //}
}

void clearWall() {
  for (int x = 0 ; x < 43  ; x++) { //move past wall
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_forward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}

void turnRight() {
  //Serial.println("Right");
  //Serial.println(val);
  for (int x = 0 ; x < 75 ; x++) { //90 deg turn
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);
  clearWall();
  delay(1000);
  turnLeft();
  delay(1000);
  

  
  //faceShelf();
  //delay(1000);
  driveToShelf();
  delay(1000);
  squareWallOne();
  delay(3000);
  turnRightShelf();
  delay(1000);
  backUp();
  delay(1000);
  CenterObject();
  delay(1000);
  TurnToPlace();
  delay(1000);
  backUp();
  delay(1000);
  //p3repMoveTowardsShelf();
  //winch();
  delay(20000000);
  /*BSALoop();
  delay(1000);
  getBlue();
  delay(1000);
  getRed();*/

}



void squareWallOne(){
  while(435> BRVal || BRVal >470 || 420> BLVal || BLVal > 445){
    while (420> BLVal || BLVal > 445){
      Serial.print("Bottom Left Distance: ");
      Serial.println(BLVal);
      BLVal = analogRead(BLSharpIR);
      if(BLVal > 420){
        for (int x = 0 ; x < 2 ; x++) {
          servoMove(leftServo, left_backward_slow);
          delay(20);
        }
      }
      delay(500);
      if(545 >BLVal){
        for (int x = 0 ; x < 2 ; x++) {
          servoMove(leftServo, left_forward_slow);
          delay(20);
        }
      }
    }
  
    delay(500);
    while (435> BRVal || BRVal >470){
      Serial.print("Bottom Right Distance: ");
      Serial.println(BRVal);
      BRVal = analogRead(BRSharpIR);
      if(BRVal > 470){
        for (int x = 0 ; x < 2 ; x++) {
        servoMove(rightServo, right_backward_slow);
        delay(20);
        }
      }
      delay(500);
      if(435 > BRVal){
        for (int x = 0 ; x < 2 ; x++) {
        servoMove(rightServo, right_forward_slow);
        delay(20);
        }
      }
     }
    

  }
  
}

void turnLeft() {
  for (int x = 0 ; x < 180 ; x++) { //90deg turn
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_forward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}

/*void faceShelf() {
  for (int x = 0 ; x < 10 ; x++) {
    BLVal = analogRead(TLSharpIR);
    BRVal = analogRead(TRSharpIR);
    if (BRVal > BLVal) {
      correctLeft();
    } else if (BLVal > BRVal) {
      correctRight();
    }
  }
  }*/

void driveToShelf() {
  while (BRVal < 550 || BLVal < 580) {
    driveForward();
    BLVal = analogRead(BLSharpIR);
    BRVal = analogRead(BRSharpIR);
    if (BRVal > 550 || BLVal > 580) {
      break;
    }
  }
}

void turnRightShelf() { //turn right to face shelf
  for (int x = 0 ; x < 72 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(5000);
 
}


void backUp() {
  for (int x = 0 ; x < 30 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);
  /*for (int x = 0 ; x < 3 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }*/
  /*for (int x = 0 ; x < 10 ; x++) {
    TLVal = analogRead(TLSharpIR);
    TRVal = analogRead(TRSharpIR);
    if (TRVal > TLVal) {
    correctLeft();
    } else if (TLVal > TRVal) {
    correctRight();
    }
    }*/
}

void winch() {
  digitalWrite (10, HIGH); //Click relay coil on
  delay(6100); //10 sec
  digitalWrite (10, LOW); //Click relay coil off
  delay (1000);
}

void servoMove(byte servoPin, int pulseWidth) {
  digitalWrite(servoPin, HIGH); // create the rising edge of the pulse
  delayMicroseconds(pulseWidth); // set pulse width in microsec
  digitalWrite(servoPin, LOW); // create the falling edge of the pulse
}


void BSALoop() {
  //buttonState = digitalRead(limitSwitch);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  while(digitalRead (5) == HIGH) {
    takeSteps(1, 1);
  }
  //getYellow();
}

void takeSteps(int steps, bool dir) {
  digitalWrite(driverDIR, dir);
  for (int x = steps; x >= 0; x--) {
    digitalWrite(driverPUL, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(driverPUL, LOW);
    delayMicroseconds(pulseDelay);
  }
}

void moveInches(double inches, bool dir) {
  double steps = inches * 975.609;
  takeSteps(ceil(steps), dir);
}

/*void getYellow() {
  while (valueYellow == 0) {
    valueYellow = digitalRead(YellowPin);
  }
  //moveInches(0, 0); // second number: 0 is up, 1 is down
  delay(1000);
  while (TRVal < 675 || TLVal < 675) {
    driveForward();
    TLVal = analogRead(TLSharpIR);
    TRVal = analogRead(TRSharpIR);
    if (TRVal > 675 || TLVal > 675) {
      break;
    }
  }
  delay(1000);
  moveInches(0.5, 0); // second number: 0 is up, 1 is down
  delay(1000);
  for (int x = 0 ; x < 200 ; x++) { //move away from the crate
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
    TLVal = analogRead(TLSharpIR);
    TRVal = analogRead(TRSharpIR);
    if (TRVal < 500 || TLVal < 500) {
      break;
    }
  }
  moveInches(4, 0); // second number: 0 is up, 1 is down
  delay(1000);
  TurnToPlace();
  delay(1000);
  dropYellow();
  delay(1000);
  moveInches(4, 0); // second number: 0 is up, 1 is down
  delay(1000);
  TurnToGrab();
  delay(1000);
  getBlue();
}*/

/*void getBlue() {

  while (valueBlue == 0) {
    valueBlue = digitalRead(BluePin);
  }

  moveInches(7.5, 0); // second number: 1 is up, 0 is down
  delay(1000);

  for (int x = 0 ; x < 25 ; x++) { //move towards the crate
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_forward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);

  moveInches(0.5, 0); // second number: 1 is up, 0 is down
  delay(1000);

  for (int x = 0 ; x < 30 ; x++) { //move away from the crate
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);
  TurnToPlace();
  delay(1000);
  stackBlue();
  delay(1000);
  TurnToGrab();
  delay(1000);
  getRed();
}*/

/*void getRed() {

  while (valueRed == 0) {
    valueRed = digitalRead(RedPin);
  }

  moveInches(10, 0); // second number: 1 is up, 0 is down
  delay(1000);

  for (int x = 0 ; x < 25 ; x++) { //move towards the crate
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_forward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);

  moveInches(0.5, 0); // second number: 1 is up, 0 is down
  delay(1000);

  for (int x = 0 ; x < 30 ; x++) { //move away the crate
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);
  TurnToPlace();
  delay(1000);
  stackRed();
  delay(1000);
  TurnToGrab();
  delay(1000);
}*/

/*void dropYellow() {
  moveInches(4.5, 1); // second number: 0 is up, 1 is down
  delay(1000);

  for (int x = 0 ; x < 200 ; x++) { //backup from dropoff
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
    BLVal = analogRead(BLSharpIR);
    BRVal = analogRead(BRSharpIR);
    if (BRVal > 500 || BLVal > 500) {
      break;
    }
  }
}

void stackBlue() {
  moveInches(4, 1); // second number: 0 is up, 1 is down
  delay(1000);

  moveInches(0.5, 1);
  delay(1000);

  for (int x = 0 ; x < 3 ; x++) { //backup from dropoff
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}*/

/*void stackRed() {
  moveInches(6, 1); // second number: 0 is up, 1 is down
  delay(1000);

  moveInches(0.5, 1);
  delay(1000);

  for (int x = 0 ; x < 3 ; x++) { //backup from dropoff
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}*/

void TurnToPlace() {
  turnLeft();
  delay(1000);
  for (int x = 0 ; x < 5 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(500);
  squareWallOne();
  delay(1000);
  turnLeft();
  delay(1000);
  driveToShelf();
  squareWallOne();
  delay(5000);//pause to simulate
}

void TurnToGrab() {
  for (int x = 0 ; x < 200 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(rightServo, right_backward_fast);
    servoMove(leftServo, left_forward_fast);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  for (int x = 0 ; x < 5 ; x++) { //This is a For-Loop see page 285 Vol 1
    driveForward();
  }
}



//RightPin = 6;
//LeftPin = 7;
//CenterPin = 8;

void CenterObject(){

  while(RightPin == HIGH || LeftPin == HIGH){
    if (RightPin == HIGH){
      //Turn a small angle to the left
      //move back a small amount
      //move a small amount to the right
    }
    if (LeftPin == HIGH){
    //Turn a small angle to the right
    //move back a small amount
    //move a small amount to the left
    }
    if (CenterPin == HIGH){
      break;
    }
  
  } 
}

