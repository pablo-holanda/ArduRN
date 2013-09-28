#include <Servo.h> 


#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100
int incomingByte;  

Servo tilt;
Servo pan;

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)

int statpin = 13;

void setup()
{
  Serial.begin(57600);
  
  pinMode(statpin, OUTPUT);
  
  tilt.attach(10);
  pan.attach(11);
  tilt.write(120);
  pan.write(85);

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }

}

void loop()
{
 
    if (Serial.available()) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.parseInt() ;
    if(incomingByte == 4 ) //p/frente
    {
    motorGo(0, CW, 50);
    motorGo(1, CCW, 50);
     delay(10);
    }

    if(incomingByte == 5 ) //p/tras
    {
      motorGo(0, CCW, 50);
      motorGo(1, CW, 50);
      delay(10);
    }
 
    if(incomingByte == 8 ) //parar
    {
      motorOff(0);
      motorOff(1);
       delay(10);
    }

    
      if(incomingByte== 2 ) //esquerda
    {
      motorGo(0, CCW, 70);
      motorGo(1, CCW, 70);
       delay(100);
    }

    
       if(incomingByte == 3 ) //direita
    {
      motorGo(0, CW, 70);
      motorGo(1, CW, 70);
       delay(100);
    }
    }

  if ((analogRead(cspin[0]) < CS_THRESHOLD) && (analogRead(cspin[1]) < CS_THRESHOLD))
    digitalWrite(statpin, HIGH);
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND
 
 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

