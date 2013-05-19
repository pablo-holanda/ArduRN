#include <Servo.h>

Servo base;
Servo cabeca;
int base1;
int cabeca1;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  base.attach(9); 
  cabeca.attach(10);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  cabeca1 = analogRead(A0);
  base1 = analogRead(A3);
  cabeca1 = constrain(cabeca1, 220, 420);
  cabeca1 = map(cabeca1, 220, 420, 0, 180);
  base1 = constrain(base1, 220, 420);
  base1 = map(base1, 220, 420, 0, 180);
  cabeca.write(cabeca1);
  delay(10);
  base.write(base1);
  delay(10);
  
  // print out the value you read:
  // delay in between reads for stability
}
