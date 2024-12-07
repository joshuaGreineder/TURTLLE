//Libraries Needed
#include<SoftwareSerial.h>


// Setup Servo Speed Values
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


// Set Camera Pins
const int RightPin = 6;
const int LeftPin = 7;
const int CenterCameraPin = 8;

// Set Camera Pin Values
int valRightPin = 0;
int valLeftPin = 0;
int valCenterCameraPin = 0;


// Set IR Sensor Pins
const int BLSharpIR = A8;
const int BRSharpIR = A7;
const int TRSharpIR = A6;
const int TLSharpIR = A5;


// Set IR Sensor Pin Values
int BLVal = 0;
int BRVal = 0;
int TRVal = 0;
int TLVal = 0;


// Setup Ball Screw Actuator
const int buttonPin = 5;         // the number of the pushbutton pin
const int ledPin = LED_BUILTIN;  // the number of the LED pin
const int driverPUL = 0;
const int driverDIR = 1;
int pulseDelay = 1000;
bool setDir = HIGH;
int limitSwitch = 5;

// Set Ball Screw Actuator Direction Parameters
const int up = 0;
const int down = 1;


// Set Winch Relay Pin
int Relay = 10;


void setup() { // Run Through Setups


  Serial.begin(9600); // Establish Baudrate

  // Servos
  pinMode(leftServo, OUTPUT); // Set Left Servo to Output
  pinMode(rightServo, OUTPUT); // Set Right Servo to Output

  // Winch Relay
  pinMode(Relay, OUTPUT); //Set the Pin Connectect to the Relay to Output

  // Camera
  pinMode(RightPin, INPUT); // Set Right Direction Pin to Input
  pinMode(LeftPin, INPUT); // Set Left Direction Pin to Input
  pinMode(CenterCameraPin, INPUT); // Set Camera Centered Pin to Input


  // Setup Stepper Controller
  pinMode (driverPUL, OUTPUT);
  pinMode (driverDIR, OUTPUT);
  pinMode(5, INPUT);
}


void loop() {


  Serial.println("Starting Program");
  //Run(); // Start Main Program


  for (int x = 0 ; x < 400 ; x++) { //90 deg turn
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }


  for (int x = 0 ; x < 400 ; x++) { //90 deg turn
    servoMove(rightServo, right_forward_fast);
    servoMove(leftServo, left_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }





}


void Run() {

  BLVal = analogRead(BLSharpIR); // Read the Bottom Left IR Sensor

  Serial.print("Bottom Left Distance: "); // Print out the value of Bottom Left IR Sensor
  Serial.println(BLVal);


  driveForward(); // Drive Forward Until Bottom Left Sensor Has a Value Greater Than 490
  if (BLVal > 500) {

    turnRight(); // Make 90 Degree Turn to Right
    delay(1000); // Wait 1 Second

    clearWall(); // Move Froward Passed Initial Wall
    delay(1000); // Wait 1 Second

    turnLeft(); // Make 90 Degree Turn to Left
    delay(1000); // Wait 1 Second

    driveToSecondWall(); // Move Towards Second Wall Until IR Sensors Read Certain Value
    delay(1000); // Wait 1 Second

    squareWall(); // Square With Wall Utilizing Both Lower IR Sensors
    delay(1000); // Wait 1 Second

    turnRightShelf(); // Turns Right Towards Shelf
    delay(1000); // Wait 1 Second

    center(); // Does a Movement That Alligns Robot More With Shelf
    delay(1000); // Wait 1 Second

    backUp(); // Backup From Shelf to Give More Clearance
    delay(500); // Wait 1 Second

    winch(); // Power Winch - Raising End Effector
    delay(1000); // Wait 1 Second

    backUp(); // Backup From Shelf to Allow Camera to See Object
    delay(1000); // Wait 1 Second

    centerObject(); // Aligns Robot Utilizing OpenMV Camera
    delay(1000); // Wait 1 Second

    getRed(); // Runs Set of Functions That in Combination Picks up Red Crate
    delay(1000); // Wait 1 Second

    make180Turn(); // Make 180 to Get in Position For Placing Object

    driveToSecondWall(); // Move Towards Second Wall Until IR Sensors Read Certain Value
    delay(1000); // Wait 1 Second

    squareWall(); // Square With Wall Utilizing Both Lower IR Sensors
    delay(1000); // Wait 1 Second


    moveInches(15.5, down); // second number: 1 is up, 0 is down
    delay(1000);

    moveInches(.15, up); // second number: 1 is up, 0 is down
    delay(1000);

    for (int x = 0 ; x < 20 ; x++) { //This is a For-Loop see page 285 Vol 1
      servoMove(leftServo, left_backward_slow);
      servoMove(rightServo, right_backward_fast);

      delay(20); // This value changes speed of motor, do not set < 20ms
    }

    delay(100000000); // Prevent Program From Exiting run()

  }
}


void make180Turn() {

  for (int x = 0 ; x < 70 ; x++) { //90 deg turn
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);

  }

  for (int x = 0 ; x < 5 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }

  for (int x = 0 ; x < 75 ; x++) { //90 deg turn
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);

  }



}


void driveForward() { // This is a subroutine for forward
  //for (int x = 0 ; x < 5  ; x++) { //This is a For-Loop see page 285 Vol 1
  servoMove(leftServo, left_forward_slow);
  servoMove(rightServo, right_forward_slow);
  delay(20); // This value changes speed of motor, do not set < 20ms
  //}
}


void clearWall() {
  for (int x = 0 ; x < 53  ; x++) { //move past wall
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_forward_slow);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}


void turnRight() {
  //Serial.println("Right");
  //Serial.println(val);
  for (int x = 0 ; x < 60 ; x++) { //90 deg turn
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}



void squareWall() {
  while ((415 > BRVal || BRVal > 440) && (420 > BLVal || BLVal > 425)) {
    while (420 > BLVal || BLVal > 425) {
      Serial.print("Bottom Left Distance: ");
      Serial.println(BLVal);

      BLVal = analogRead(BLSharpIR);
      if (BLVal > 420) {
        for (int x = 0 ; x < 2 ; x++) {
          servoMove(leftServo, left_backward_fast);


          delay(20);
        }
      }
      delay(500);
      if (525 > BLVal) {
        for (int x = 0 ; x < 2 ; x++) {
          servoMove(leftServo, left_forward_slow);


          delay(20);
        }
      }
    }

    delay(500);
    while (415 > BRVal || BRVal > 440) {
      Serial.print("Bottom Right Distance: ");
      Serial.println(BRVal);
      BRVal = analogRead(BRSharpIR);
      if (BRVal > 440) {
        for (int x = 0 ; x < 2 ; x++) {
          servoMove(rightServo, right_backward_fast);


          delay(20);
        }
      }
      delay(500);
      if (415 > BRVal) {
        for (int x = 0 ; x < 2 ; x++) {
          servoMove(rightServo, right_forward_slow);


          delay(20);
        }
      }
    }


  }

}

void turnLeft() {
  for (int x = 0 ; x < 179 ; x++) { //90deg turn
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_forward_slow);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}


void driveToSecondWall() {
  while (BRVal < 500 || BLVal < 530) {
    driveForward();
    BLVal = analogRead(BLSharpIR);
    BRVal = analogRead(BRSharpIR);

    if (BRVal > 500 || BLVal > 530) {
      break;
    }
  }
}

void turnRightShelf() { //turn right to face shelf
  for (int x = 0 ; x < 79 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_forward_fast);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}


void backUp() {
  for (int x = 0 ; x < 20 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
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


void getRed() {
  Serial.println("getting red");
  moveInches(4.10, up); // second number: 1 is up, 0 is down
  delay(1000);
  TLVal = analogRead(TLSharpIR);

  while (TLVal < 780) {
    TLVal = analogRead(TLSharpIR);
    //move towards the crate
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_forward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);

  moveInches(0.40, up);
  delay(1000);
  TLVal = analogRead(TLSharpIR);
  while (TLVal > 300) {
    TLVal = analogRead(TLSharpIR);
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);
  moveInches(4.10, down);
  delay(1000);

}



/*void placeRed() {
  moveInches(6, down);
  delay(1000);

  moveInches(0.25, down);
  delay(1000);

  for (int x = 0 ; x < 3 ; x++) { //backup from dropoff
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_slow);
    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  }*/

void TurnToPlace() {
  for (int x = 0 ; x < 190 ; x++) { //90deg turn
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_forward_slow);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(1000);
  for (int x = 0 ; x < 2 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(500);
  squareWall();
  delay(1000);
  turnLeft();
  delay(1000);
  driveToSecondWall();
  squareWall();
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
//CenterCameraPin = 8;

void centerObject() {
  Serial.println("Calibration");
  valRightPin = digitalRead(RightPin);
  valLeftPin = digitalRead(LeftPin);
  valCenterCameraPin = digitalRead(CenterCameraPin);


  Serial.println(valRightPin);
  Serial.println(valLeftPin);
  Serial.println(valCenterCameraPin);

  if (valLeftPin == LOW && valRightPin == LOW && valCenterCameraPin == LOW) {
    while (valLeftPin == LOW && valRightPin == LOW && valCenterCameraPin == LOW) {
      servoMove(leftServo, left_backward_slow);
      servoMove(rightServo, right_backward_fast);
      delay(20);

      Serial.println("All pins Low, object not detected");
      delay(20); // This value changes speed of motor, do not set < 20ms
      if (valLeftPin == HIGH || valRightPin == HIGH || valCenterCameraPin == HIGH) {
        Serial.println("Fixed, object now detected");
        break;
      }
    }
  }

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

        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(500);

      //move back a small amount
      /*for (int x = 0 ; x < 8 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_backward_slow);
        servoMove(rightServo, right_backward_fast);

        delay(20); // This value changes speed of motor, do not set < 20ms
        }*/
      delay(500);
      //move a small amount to the right
      for (int x = 0 ; x < 50 ; x++) {
        servoMove(rightServo, right_backward_slow);
        servoMove(leftServo, left_forward_slow);

        delay(20); // This value changes speed of motor, do not set < 20
      }
      delay(500);
      //move forward same small ammount
      for (int x = 0 ; x < 4 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_forward_slow);
        servoMove(rightServo, right_forward_slow);

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

        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(500);

      //move back a small amount
      for (int x = 0 ; x < 7 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_backward_slow);
        servoMove(rightServo, right_backward_fast);

        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(500);
      //move a small amount to the left
      for (int x = 0 ; x < 30 ; x++) {
        servoMove(rightServo, right_forward_slow);
        servoMove(leftServo, left_backward_slow);

        delay(20); // This value changes speed of motor, do not set < 20
      }
      delay(500);
      //move forward same small ammount
      for (int x = 0 ; x < 4 ; x++) { //This is a For-Loop see page 285 Vol 1
        servoMove(leftServo, left_forward_slow);
        servoMove(rightServo, right_forward_slow);

        delay(20); // This value changes speed of motor, do not set < 20ms
      }
      delay(3000);
    }

    if (valLeftPin == LOW && valRightPin == LOW && valCenterCameraPin == LOW) {
      while (valLeftPin == LOW && valRightPin == LOW && valCenterCameraPin == LOW) {
        servoMove(leftServo, left_backward_slow);
        servoMove(rightServo, right_backward_fast);
        delay(20);

        Serial.println("All pins Low, object not detected");
        delay(20); // This value changes speed of motor, do not set < 20ms
        if (valLeftPin == HIGH || valRightPin == HIGH || valCenterCameraPin == HIGH) {
          Serial.println("Fixed, object now detected");
          break;
        }
      }
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

void center() {
  //Turn a small angle to the right
  for (int x = 0 ; x < 30 ; x++) {
    servoMove(rightServo, right_backward_slow);
    servoMove(leftServo, left_forward_slow);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(500);

  //move back a small amount
  for (int x = 0 ; x < 30 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_backward_slow);
    servoMove(rightServo, right_backward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
  delay(500);
  //move a small amount to the left
  for (int x = 0 ; x < 30 ; x++) {
    servoMove(rightServo, right_forward_slow);
    servoMove(leftServo, left_backward_slow);

    delay(20); // This value changes speed of motor, do not set < 20
  }
  delay(500);
  //move forward same small ammount
  for (int x = 0 ; x < 8 ; x++) { //This is a For-Loop see page 285 Vol 1
    servoMove(leftServo, left_forward_slow);
    servoMove(rightServo, right_forward_fast);

    delay(20); // This value changes speed of motor, do not set < 20ms
  }
}



