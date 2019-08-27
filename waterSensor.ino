// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int sensorPin = 34;

#define LEDPIN 2

#define MOTORPIN 26

// variable for storing the potentiometer value
int sensorValue = 0;
int MAX_VALUE = 4095;
int MIN_VALUE = 1200;

unsigned long TIMEBEFORENEXTTEST = 10000;

unsigned long lastTimeWhenChecked = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN,OUTPUT);
  pinMode(MOTORPIN,OUTPUT);
  delay(1000);

  lastTimeWhenChecked = millis();
}

void loop() {
  // Reading potentiometer value
  sensorValue = analogRead(sensorPin);
  double sensorDouble = double(sensorValue-MIN_VALUE)/double(MAX_VALUE-MIN_VALUE);

  double timeSinceLastCheck = millis() - lastTimeWhenChecked ;
  
  if(sensorDouble > 0.45 && timeSinceLastCheck > TIMEBEFORENEXTTEST)
  {
    digitalWrite(LEDPIN,HIGH);
    digitalWrite(MOTORPIN, HIGH);
    delay(3000);
    lastTimeWhenChecked = millis();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(MOTORPIN, LOW);
  }
  
  Serial.println(sensorDouble);
  delay(500);
}
