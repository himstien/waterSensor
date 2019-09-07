#include "WifiConfig.h"

#include "CloudSettings.h"

// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int sensorPinCap = 35;
const int sensorPinRes = 34;

#define LEDPIN 2

#define MOTORPIN 26

// variable for storing the potentiometer value
int sensorValueRes = 0;
int sensorValueCap = 0;
int MAX_VALUE = 4095;
int MIN_VALUE = 1200;

unsigned long TIME_BEFORE_NEXT_TEST = 30000;
unsigned long TIME_MOTOR_ON = 5000;

unsigned long lastTimeWhenChecked = 0;

double WATER_THRESHOLD = 0.6;

double sensorDouble = 0.0;

void setup() {
  Serial.begin(115200);

  //wifiMulti.addAP(ssidLab, passLab);
  wifiMulti.addAP(ssidHome, passHome);

    // CONNECT TO WIFI
  int numAttmpt = 0;
  while (wifiMulti.run() != WL_CONNECTED && numAttmpt < 10)
  {
    delay(500);
    Serial.print(".");
    numAttmpt++; 
  }
  if(numAttmpt < 10)
  {
    WiFiStatus = WIFI_CONNECTED;
    Serial.println("");
    Serial.println("WiFi connected");
  }
  else
  {
    WiFiStatus = WIFI_UNAVAILABLE;
    Serial.println("");
    Serial.println("Couldn't connet to WiFi");
  }

  pinMode(LEDPIN,OUTPUT);
  pinMode(MOTORPIN,OUTPUT);
  delay(1000);

  lastTimeWhenChecked = millis();
  TIME_SINCE_LAST_SEND = millis();
}

void loop() {
  // Reading potentiometer value
  sensorValueRes = analogRead(sensorPinRes);
  sensorValueCap = analogRead(sensorPinCap);
//  sensorDouble = double(sensorValueRes-MIN_VALUE)/double(MAX_VALUE-MIN_VALUE);
  sensorDouble = double(sensorValueCap)/double(4095);

//  sensorDouble = 0.0; 
  double timeSinceLastCheck = millis() - lastTimeWhenChecked ;
  
  if(sensorDouble > WATER_THRESHOLD && timeSinceLastCheck > TIME_BEFORE_NEXT_TEST)
  {
    digitalWrite(LEDPIN,HIGH);
    digitalWrite(MOTORPIN, HIGH);
    delay(TIME_MOTOR_ON);
    lastTimeWhenChecked = millis();
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(MOTORPIN, LOW);
  }
  
  Serial.println(sensorDouble);
  Serial.println("Sensor value resistive" + String( sensorValueRes));
  Serial.println("Sensor value capicitive" + String( sensorValueCap));

  if(millis() - TIME_SINCE_LAST_SEND > RATE_SEND_DATA)
  {
    SendData();
    TIME_SINCE_LAST_SEND = millis();    
  }
  
  delay(1000);
  
}


void SendData()
{  

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(server, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = apiKey;
    data_to_send += "&field1=";
    data_to_send += String(sensorDouble);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(100);
  }
  client.stop();
}
