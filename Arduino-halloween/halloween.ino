/*

  Halloween Project 2018

  www.starthardware.org
  www.arduino-tutorial.de

  CC-BY-NC-SA
  Stefan Hermann

*/


#include <Servo.h>

int ledPin = 7;
int servoEyesPin = 2;
int servoFogPin = 3;
int irPin = A0;
int irThreshold = 300;    // threshold when a hand is close to the sensor

long fogTimer = 0;
int fogTimeout = 2000;    // time until fog shall apear

boolean fogDone = false;

Servo myServoEyes, myServoFog;

void fog() {
    delay(random(1000));
    myServoFog.write(15);
    delay(300);
    myServoFog.write(0);
}

void eyesOn() {
  if (millis()%4000<10){    
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    }
  digitalWrite(ledPin, HIGH);
  myServoEyes.write(180);
}

void eyesOff() {
  digitalWrite(ledPin, LOW);
  myServoEyes.write(0);
}

void setup() {
  Serial.begin(115200);
  myServoEyes.attach(servoEyesPin);
  myServoFog.attach(servoFogPin);
  pinMode(ledPin, OUTPUT);
  myServoFog.write(0);
  myServoEyes.write(0);
}

void loop() {
  Serial.println(analogRead(irPin));
  if (analogRead(irPin) > irThreshold) {
    eyesOn();
    if ((fogTimer+fogTimeout<millis())&&(fogDone==false)){
        fog();
        fogDone=true;
    }
  } else {
    eyesOff();
    fogTimer = millis();
    fogDone = false;
  }
  delay(10);
}
