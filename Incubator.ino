 
    int ledPinRed = 2; //levelLED
    int ledPinBlue = 3; //turbidityLED
    int ledPinGreen = 4; //phLED
    int levelPin = 5; //pullup pin
    int motorPin1 = 6; 
    int motorPin2 = 9; 
    int motorPin3 = 10; 
    int motorPin4 = 11; 
    //pins for the sensors
    int level_pin = A0;
    int pH_pin = A1;
    int turbidity_pin = A2;
    int level;
    double ph;
    double turbidity;
    
//i. Starting/Stopping the stirrer motor.
void Motor(){
  // This code will turn Motor & Impeller clockwise.
  analogWrite(motorPin1, 180);
  analogWrite(motorPin2, 0);
  delay(1000); 
}

void smoothStartMotor(){
  // This code will turn Motor & Impeller clockwise.
  int i;
  for (i=0; i<=180; i=i+10)
  {  
  analogWrite(motorPin1, i);
  delay(100);
  }
  analogWrite(motorPin2, 0);
  }

void smoothStopMotor(){
  // This code will turn Motor & Impeller clockwise.
 int i;
  for (i=180; i>=0; i=i-10){  
  analogWrite(motorPin1, i);
  delay(100);
  }
  analogWrite(motorPin2, 0);
  }

//ii. Starting/Stopping the peristaltic pump.
void Pump(){
  analogWrite(motorPin3, 180);
  analogWrite(motorPin4, 0);
  delay(1000);
  }
void startPump(){
  int i;
  for (i=0; i<=180; i=i+10){  
  analogWrite(motorPin3, i);
  delay(100);
  }
  analogWrite(motorPin4, 0);
  
}
void stopPump(){
int i;
  for (i=180; i>=0; i=i-10){  
  analogWrite(motorPin3, i);
  delay(100);
  }
  analogWrite(motorPin4, 0);
}

//Turning led for switch
void led(int level, double turbidity, double ph)
{
  if(level == 0){
     digitalWrite(ledPinRed, HIGH);
  }
  else{
     digitalWrite(ledPinRed, LOW);
  }
  //value for turbidity  is approximate ( must analyze the best value)
  if(turbidity > 14.5){
     digitalWrite(ledPinBlue, HIGH);
  }
  else{
     digitalWrite(ledPinBlue, LOW);
  }
  //value for ph is approximate
  if(ph < 9.0){
     digitalWrite(ledPinBlue, HIGH);
  }
  else{
     digitalWrite(ledPinBlue, LOW);
  }
}

double phMeasure()
{
 int pH_sensorValue = analogRead(pH_pin);
 // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
 float pH_voltage = pH_sensorValue * 5.0 / 1023.0;
 Serial.println(pH_voltage);
 float pH_value = - 5.02456 * pH_voltage + 21.477848;
 delay(100);
 return pH_value;
}

double turbidityMeasure(){
  turbidity = analogRead(turbidity_pin);//range from 0 to 1023
  return turbidity;
  }


void setup() {
    Serial.begin(9600);
    pinMode(ledPinRed, OUTPUT);
    pinMode(ledPinGreen, OUTPUT);
    pinMode(ledPinBlue, OUTPUT);
    pinMode(levelPin, INPUT_PULLUP);
    pinMode(motorPin1, OUTPUT); 
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT); 
    pinMode(motorPin4, OUTPUT);
    smoothStartMotor();
}


void loop() {
  level = digitalRead(levelPin);
  turbidity = turbidityMeasure();
  ph = phMeasure();

  //write the values on monitor
  Serial.print("ph: ");
  Serial.println(ph);
  Serial.print("turbidity: ");
  Serial.println(turbidity);
  Serial.print("level: ");
  Serial.println(level);
  
  //turn on leds according to the measurements
  led(level, turbidity, ph);
  Motor();
  
  if(ph<6){
    startPump();//adding Sodium hydroxide
    //smoothStopMotor();
    }
  if(level == 0){
    smoothStopMotor();
    //stopPump(); just in case maybe (?)
    }
  if(turbidity > 15.5){
    smoothStopMotor();
    //stopPump(); just in case maybe (?)
    }
  
}


