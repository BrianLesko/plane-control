// Brian Lesko 
// Controls the steering for 3 servos and the throttle for an brushless DC motor

#include <Servo.h>

//create servo objects
Servo steering; 
Servo throttle;
Servo rearServo1;
Servo rearServo2;

int ledPin = 13;
int center = 95;
int right = 55;
int left = 130;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
 
  steering.attach(9);   // attach steering servo to pin 9
  throttle.attach(10);  // attach ESC to pin 10

  rearServo1.attach(7); // Rear steering servos
  rearServo2.attach(8);
 
  steering.write(95);   // centers steering
  rearServo1.write(95);
  rearServo2.write(95);
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
    else if (incomingMessage.startsWith("servo:")) {
      int angle = incomingMessage.substring(6).toInt();
      steering.write(angle);
      if (previousPower < 120) {
        rearServo1.write(angle);
        rearServo2.write(angle);
      }
    }
  }
}