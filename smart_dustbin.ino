
#define BLYNK_TEMPLATE_ID "TMPL3xeqpReOi"
#define BLYNK_TEMPLATE_NAME "Blynk Smart Dustbin"
#define BLYNK_AUTH_TOKEN "6gZZ0br1YgBMJgTpA7OIwXsy6WCUhHIS"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "OnePlus Nord 2T 5G";
char pass[] = "g9pajn32";

BlynkTimer timer;

#define echoPin D5
#define trigPin D6
#include<Servo.h>
Servo servo;
long duration;
int distance; 
int binLevel=0;

void SMESensor()
{
  int ir=digitalRead(D7);
  if(ir==HIGH)
  {    
    servo.write(90);
    for(int i=0; i<50; i++)
    {
      Blynk.virtualWrite(V2, 90);
      ultrasonic(); 
      delay(100);
    }
    servo.write(0);
    Blynk.virtualWrite(V2, 0);
  }
  if(ir==LOW)
  {
    
    ultrasonic();
    delay(200);
  }
}
void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 21, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);
}
void setup()
{
  Serial.begin(9600);
  servo.attach(D2);
  pinMode(D7, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
   Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(1000L, SMESensor);
}

void loop() 
{
  Blynk.run();
  timer.run();
}
