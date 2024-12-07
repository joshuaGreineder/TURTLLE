/* servoMotionModuleBookBuild.ino by C.d.odom on 2.17.2015.
   A wheeled robot servo SKETCH.
*/

// GLOBALS
//const int leftServoPin = 1;               // servo pin for LEFT wheel
//const int rightServoPin = 2;              // servo pin for RIGHT wheel
//const int LEDPin = 13;                    // the onboard LED pin (for diagnostics)

// Left Servo Pulse Width Constants
const int left_forward_fast = 2000;       // CCW Fast
const int left_forward_slow = 1600;       // CCW Slow
const int left_stop = 1500;               // Center position
const int left_reverse_slow = 1400;       // CW Slow
const int left_reverse_fast = 1000;       // CW Fast

// Right Servo Pulse Width Constants
const int right_forward_fast = 1000;      // CW Fast
const int right_forward_slow = 1400;      // CW Slow
const int right_stop = 1500;              // Center position
const int right_reverse_slow = 1600;      // CCW Slow
const int right_reverse_fast = 2000;      // CCW Fast



// These movement functions are the HIGHEST LEVEL commands. They cause the robot to
// take a certain number of steps in the designated direction and speed, or to stop
// for a certain number of "steps". These functions call the "step" functions below.

void robotStop(int x) {
  for (int i = 0; i <= x ; i++) {
    stopStep();     // a hard stop (not a coasting stop)
  }
}

void forwardFast(int x) {
  for (int i = 0; i <= x ; i++) {
    forwardStepFast();
  }
}

void forwardSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    forwardStepSlow();
  }
}
//replace int x later
void reverseFast(int x) {
  for (int i = 0; i <= x ; i++) {
    reverseStepFast();
  }
}

void reverseSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    reverseStepSlow();
  }
}

void rightFast(int x) {
  for (int i = 0; i <= x ; i++) {
    rightStepFast();
  }
}

void rightSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    rightStepSlow();
  }
}

void leftFast(int x) {
  for (int i = 0; i <= x ; i++) {
    leftStepFast();
  }
}

void leftSlow(int x) {
  for (int i = 0; i <= x ; i++) {
    leftStepSlow();
  }
}


// These "step" functions are the SECOND LOWEST LEVEL of the movement commands. They are
// used to turn both servo wheels in concert to make the robot take exactly one step in
// some direction, or to send a hard stop to both wheels.  This is done by calling the
// createPulse() function, once for each wheel. It is CRITICAL that you keep the 20ms
// delay, because it is necessary to give the motors time to respond!

void stopStep() {
  createPulse(leftServoPin, left_stop);
  createPulse(rightServoPin, right_stop);
  delay(20);      // do NOT alter this delay time!
}

void forwardStepFast() {
  createPulse(leftServoPin, left_forward_fast);
  createPulse(rightServoPin, right_forward_fast);
  delay(20);      // do NOT alter this delay time!
}

void forwardStepSlow() {
  createPulse(leftServoPin, left_forward_slow);
  createPulse(rightServoPin, right_forward_slow);
  delay(20);      // do NOT alter this delay time!
}

void reverseStepFast() {
  createPulse(leftServoPin, left_reverse_fast);
  createPulse(rightServoPin, right_reverse_fast);
  delay(20);      // do NOT alter this delay time!
}

void reverseStepSlow() {
  createPulse(leftServoPin, left_reverse_slow);
  createPulse(rightServoPin, right_reverse_slow);
  delay(20);      // do NOT alter this delay time!
}

void rightStepSlow() {
  createPulse(leftServoPin, left_forward_slow);
  createPulse(rightServoPin, right_reverse_slow);
  delay(20);      // do NOT alter this delay time!
}

void leftStepSlow() {
  createPulse(leftServoPin, left_reverse_slow);
  createPulse(rightServoPin, right_forward_slow);
  delay(20);      // do NOT alter this delay time!
}

void rightStepFast() {
  createPulse(leftServoPin, left_forward_fast);
  createPulse(rightServoPin, right_reverse_fast);
  delay(20);      // do NOT alter this delay time!
}

void leftStepFast() {
  createPulse(leftServoPin, left_reverse_fast);
  createPulse(rightServoPin, right_forward_fast);
  delay(20);      // do NOT alter this delay time!
}


// createPulse() is the LOWEST LEVEL (most basic) of the movement commands.
// It simply creates a single pulse of a given pulse width on a given pin.
// This command makes ONE servo (set by the servoPin variable) take ONE
// step whose speed and direction is set by the pulseWidth variable.

void createPulse(byte servoPin, int pulseWidth) {
  // take one step with one servo
  digitalWrite(servoPin, HIGH);        // create the rising edge of the pulse
  delayMicroseconds(pulseWidth);       // precisely set pulse width in microseconds!
  digitalWrite(servoPin, LOW);         // create the falling edge of the pulse
}
