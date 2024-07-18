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
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
 
  throttle.attach(12,1000,2000);  // attach ESC to pin 10 and set the min and max pulse width micro seconds
  left.attach(11); // left servo on pin 7
  right.attach(10); // right servo on pin 8
 
  left.write(95); //centers the servos
  right.write(95);
  //arm the ESC
  throttle.writeMicroseconds(2000); // max throttle
  delay(2000);  // Wait for 2 seconds
  throttle.writeMicroseconds(1000);  // minimum throttle
  delay(2000);  // Wait for 2 seconds
}

void loop() {
  if (Serial.available() > 0) {
    String incomingMessage = Serial.readStringUntil('\n');

    if (incomingMessage.startsWith("throttle:")) {
      int power = incomingMessage.substring(9).toInt();
      throttle.write(power);
    } 
    else if (incomingMessage.startsWith("left:")) {
      int angle = incomingMessage.substring(5).toInt();
      left.write(angle);
    }
    else if (incomingMessage.startsWith("right:")) {
      int angle = incomingMessage.substring(6).toInt();
      right.write(angle);
    }
  }
}