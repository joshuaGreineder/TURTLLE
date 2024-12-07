
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
const int right_forward_slow = 1240;
const int right_stop = 1500; // Center position
const int right_forward_fast = 1000;
const int right_backward_slow = 1750;// CCW

//For Camera
const int RightPin = 6;
const int LeftPin = 7;
const int CenterCameraPin = 8;


//Sensor
const int BLSharpIR = A8;
const int BRSharpIR = A7;
const int TRSharpIR = A6;
const int TLSharpIR = A5;
int BLVal = 0;
int BRVal = 0;
int TRVal = 0;
int TLVal = 0;

//Radio delay
const int Radio5Delay = 11;
const int Radio30Delay = 12;

int valRadio5Delay = 0;
int valRadio30Delay = 0;

int valRightPin = 0;
int valLeftPin = 0;
int valCenterCameraPin = 0;


//BSA constants
const int buttonPin = 5;         // the number of the pushbutton pin
const int ledPin = LED_BUILTIN;  // the number of the LED pin
const int driverPUL = 0;
const int driverDIR = 1;
int pulseDelay = 1000;
bool setDir = HIGH;
int limitSwitch = 5;
const int up = 0;
const int down = 1;


//BSA variables will change:
//int buttonState = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(5000);
  Serial.println("Initializing Program");
  pinMode(leftServo, OUTPUT);
  pinMode(rightServo, OUTPUT);

  //radio delay
  pinMode(Radio5Delay, INPUT);
  pinMode(Radio30Delay, INPUT);

  //For Camera
  pinMode(RightPin, INPUT);
  pinMode(LeftPin, INPUT);
  pinMode(CenterCameraPin, INPUT);

  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
  pinMode(5, INPUT);
  Serial.println("Starting Drive");
  //centerObject();
  delay(1000);
  Serial.println("Squared");
  getRed();
  //moveInches(5, up); // second number: 1 is up, 0 is down
  Serial.println("BSA moved");
}
void loop() {
  valRightPin = digitalRead(RightPin);
  valLeftPin = digitalRead(LeftPin);
  valCenterCameraPin = digitalRead(CenterCameraPin);
  delay(1000);
  Serial.println(valRightPin);
  Serial.println(valLeftPin);
  Serial.println(valCenterCameraPin);
}


void servoMove(byte servoPin, int pulseWidth) {
  digitalWrite(servoPin, HIGH); // create the rising edge of the pulse
  delayMicroseconds(pulseWidth); // set pulse width in microsec
  digitalWrite(servoPin, LOW); // create the falling edge of the pulse
}

void CheckForDelay() {
  valRadio5Delay = digitalRead(Radio5Delay);
  valRadio30Delay = digitalRead(Radio30Delay);
  if (valRadio5Delay == HIGH) {
    Serial.println("5 second delay");
    servoMove(leftServo, left_stop);
    servoMove(rightServo, right_stop);
    delay(6000);
  }
  if (valRadio30Delay == HIGH) {
    Serial.println("30 second delay");
    servoMove(leftServo, left_stop);
    servoMove(rightServo, right_stop);
    delay(35000);
  }
}

void ZeroBSA() {
  //buttonState = digitalRead(limitSwitch);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  while (digitalRead (5) == HIGH) {
    takeSteps(1, 1);
  }
}

//BSA Functions

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








//Camera Center Function
//RightPin = 6;
//LeftPin = 7;
//CenterCameraPin = 8;

void centerObject() {
  Serial.println("Calibration");
  valRightPin = digitalRead(RightPin);
  valLeftPin = digitalRead(LeftPin);
  valCenterCameraPin = digitalRead(CenterCameraPin);


  Serial.println(valRightPin);
  Serial.println(valLeftPin);
  Serial.println(valCenterCameraPin);
  while (valRightPin == HIGH || valLeftPin == HIGH) {
    valRightPin = digitalRead(RightPin);
    valLeftPin = digitalRead(LeftPin);
    valCenterCameraPin = digitalRead(CenterCameraPin);
    Serial.println(valRightPin);
    Serial.println(valLeftPin);
    Serial.println(valCenterCameraPin);
    if (valRightPin == HIGH) {
      valRightPin = digitalRead(RightPin);
      valLeftPin = digitalRead(LeftPin);
      valCenterCameraPin = digitalRead(CenterCameraPin);
      Serial.println("Moving Right");
      //Turn a small angle to the left
      for (int x = 0 ; x < 45 ; x++) {
        servoMove(leftServo, left_backward_slow);
        servoMove(rightServo, right_forward_slow);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(500);

      //move back a small amount
      /*for (int x = 0 ; x < 8 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_backward_slow);
        servoMove(rightServo, right_backward_fast);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20ms
        }*/
      delay(500);
      //move a small amount to the right
      for (int x = 0 ; x < 50 ; x++) {
        servoMove(rightServo, right_backward_slow);
        servoMove(leftServo, left_forward_slow);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20
      }
      delay(500);
      //move forward same small ammount
      for (int x = 0 ; x < 7 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_forward_slow);
        servoMove(rightServo, right_forward_slow);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(3000);
    }
    if (valLeftPin == HIGH) {
      valRightPin = digitalRead(RightPin);
      valLeftPin = digitalRead(LeftPin);
      valCenterCameraPin = digitalRead(CenterCameraPin);
      Serial.println("Moving Left");
      //Turn a small angle to the right
      for (int x = 0 ; x < 15 ; x++) {
        servoMove(rightServo, right_backward_slow);
        servoMove(leftServo, left_forward_slow);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(500);

      //move back a small amount
      for (int x = 0 ; x < 7 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_backward_slow);
        servoMove(rightServo, right_backward_fast);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(500);
      //move a small amount to the left
      for (int x = 0 ; x < 30 ; x++) {
        servoMove(rightServo, right_forward_slow);
        servoMove(leftServo, left_backward_slow);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20
      }
      delay(500);
      //move forward same small ammount
      for (int x = 0 ; x < 6 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_forward_slow);
        servoMove(rightServo, right_forward_slow);
        CheckForDelay();
        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(3000);
    }
    if (valCenterCameraPin == HIGH) {
      Serial.println(valRightPin);
      Serial.println(valLeftPin);
      Serial.println(valCenterCameraPin);
      Serial.println("Squared");
      break;
    }

  }
}

void getRed() {
  BLVal = analogRead(BLSharpIR);
  BRVal = analogRead(BRSharpIR);
  Serial.println("getting red");

  moveInches(5.5, up); // second number: 1 is up, 0 is down
  delay(1000);

  //move to wall

  while (BLVal < 400) {
    driveForward();
    BLVal = analogRead(BLSharpIR);
    BRVal = analogRead(BRSharpIR);
  }
  delay(500);

  moveInches(0.5, up); // second number: 1 is up, 0 is down
  delay(1000);


  while (BLVal > 300) {

    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }


  delay(1000);
  moveInches(5.75, down); // second number: 1 is up, 0 is down
  delay(1000);

}
void driveForward() { // This is a subroutine for forward
  servoMove(leftServo, left_forward_slow);
  servoMove(rightServo, right_forward_slow);
  CheckForDelay();
  delay(20); // This value changes speed of motor, do not set < 20ms
}





