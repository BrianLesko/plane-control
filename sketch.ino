// Brian Lesko 
// Controls the steering for 2 servos and the throttle for a brushless DC motor

#include <Servo.h>

//create servo objects
Servo throttle;
Servo left;
Servo right;

int ledPin = 13;
int center = 95;
//int right = 55;
//int left = 130;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
 
  throttle.attach(10);  // attach ESC to pin 10
  left.attach(7); // left servo on pin 7
  right.attach(8); // right servo on pin 8
 
  left.write(95); //centers the servos
  right.write(95);
  throttle.write(90);   // sets mid throttle
}

int previousPower = 0;

void loop() {
  if (Serial.available() > 0) {
    String incomingMessage = Serial.readStringUntil('\n');

    if (incomingMessage.startsWith("throttle:")) {
      int power = incomingMessage.substring(9).toInt();
      // If the new power is significantly lower than the previous power, decrease it gradually
      if (power < previousPower - 2) { 
        power = previousPower - 2; 
      }
      // If the new power is significantly higher than the previous power, increase it gradually
      else if (power > previousPower + 2) { 
        power = previousPower + 2;
      }
      throttle.write(power);
      previousPower = power;
    } 
    else if (incomingMessage.startsWith("left:")) {
      int angle = incomingMessage.substring(6).toInt();
      left.write(angle);
    }
    else if (incomingMessage.startsWith("right:")) {
      int angle = incomingMessage.substring(6).toInt();
      right.write(angle);
    }
  }
}