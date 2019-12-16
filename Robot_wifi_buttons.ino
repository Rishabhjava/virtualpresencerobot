
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests tnb o the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3c78e5687b02475ba07ae74b70f652a4";
int speed_motor_l;
int speed_motor_r;
// Your WiFi credentials.
// Set password to "" for open networks.
#include <Ticker.h>
Ticker ticker;

// These are used to set the direction of the bridge driver.
#define ENB D7      //ENB
#define MOTORB_1 D6 //IN3
#define MOTORB_2 D5 //IN4
#define MOTORA_1 D4 //IN1
#define MOTORA_2 D3 //IN2
#define ENA D2      //ENA
#define LED_PIN 2
void tick()
{
  int state = digitalRead(LED_PIN);
  digitalWrite(LED_PIN, !state);
}
void configModeCallback (WiFiManager *myWiFiManager) {
  ticker.attach(0.2, tick);
}
// SETUP
void setup()
{
  WiFiManager wifiManager;
  // Configure pins
  pinMode(ENA, OUTPUT);
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);

  // Start serial communication
  Serial.begin(9600);
  ticker.attach(0.6, tick);
  wifiManager.setAPCallback(configModeCallback);
  if (!wifiManager.autoConnect("Ap Name")) {                          //    your ap name
    ESP.reset();
    delay(20000);
  }
  ticker.detach();
  // Connect Blynk
  Blynk.config(auth);
}

BLYNK_WRITE(V4){
  speed_motor_r = param.asInt();
  Serial.println(speed_motor_r);
  
}
BLYNK_WRITE(V5){
  speed_motor_l = param.asInt();
  Serial.println(speed_motor_l);
  
}
// FORWARD
BLYNK_WRITE(V0) {
  speed_motor_l=speed_motor_l;
  speed_motor_r=speed_motor_r;
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving forward");
    analogWrite(ENA, speed_motor_l);
    analogWrite(ENB, speed_motor_r);
    digitalWrite(MOTORA_1, HIGH);
    digitalWrite(MOTORA_2, LOW);
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, HIGH);
  }
  else {
    Serial.println("Stop");
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, LOW);
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, LOW);
  }
}

// RIGHT
BLYNK_WRITE(V1) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning right");
    analogWrite(ENA, speed_motor_l);
    analogWrite(ENB, speed_motor_r);
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, HIGH);
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, HIGH);
  }
  else {
    Serial.println("Stop");
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, LOW);
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, LOW);
  }
}

// LEFT
BLYNK_WRITE(V2) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Turning right");
    analogWrite(ENA, speed_motor_l);
    analogWrite(ENB, speed_motor_r);
    digitalWrite(MOTORA_1, HIGH);
    digitalWrite(MOTORA_2, LOW);
    digitalWrite(MOTORB_1, HIGH);
    digitalWrite(MOTORB_2, LOW);
  }
  else {
    Serial.println("Stop");
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, LOW);
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, LOW);
  }
}

// BACKWARD
BLYNK_WRITE(V3) {
  int button = param.asInt(); // read button
  if (button == 1) {
    Serial.println("Moving backward");
    analogWrite(ENA, speed_motor_l);
    analogWrite(ENB, speed_motor_r);
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, HIGH);
    digitalWrite(MOTORB_1, HIGH);
    digitalWrite(MOTORB_2, LOW);
  }
  else {
    Serial.println("Stop");
    analogWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
    digitalWrite(MOTORA_1, LOW);
    digitalWrite(MOTORA_2, LOW);
    digitalWrite(MOTORB_1, LOW);
    digitalWrite(MOTORB_2, LOW);
  }
}

// MAIN CODE
void loop()
{
  Blynk.run();
}
