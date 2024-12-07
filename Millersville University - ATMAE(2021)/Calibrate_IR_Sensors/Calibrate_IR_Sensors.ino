
//Sensor
const int BLSharpIR = A8;
const int BRSharpIR = A7;
const int TRSharpIR = A6;
const int TLSharpIR = A5;
int BLVal = 0;
int BRVal = 0;
int TRVal = 0;
int TLVal = 0;


void setup(){
  
  pinMode(BLSharpIR, INPUT);
  pinMode(BRSharpIR, INPUT);
  pinMode(TLSharpIR, INPUT);
  pinMode(TRSharpIR, INPUT);
  
  Serial.begin(9600);
  
  while(!Serial);
}

void loop(){
  BLVal = analogRead(BLSharpIR);
  BRVal = analogRead(BRSharpIR);
  TLVal = analogRead(TLSharpIR);
  TRVal = analogRead(TRSharpIR);

  Serial.print("Bottom Right Distance: ");
  Serial.println(BRVal);
  
  Serial.print("Bottom Left Distance: ");
  Serial.println(BLVal);

  Serial.print("Top Right Distance: ");
  Serial.println(TRVal);
  
  Serial.print("Top Left Distance: ");
  Serial.println(TLVal);
  
  delay(5);
}

