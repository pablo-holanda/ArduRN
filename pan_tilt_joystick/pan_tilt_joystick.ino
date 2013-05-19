#include <Servo.h> 

#define BAUDRATE 19200

Servo base;
Servo cabeca;

int xjoystick;
int yjoystick;
int parar;



void setup()
{ 
  Serial.begin(BAUDRATE);
  base.attach(9); 
  cabeca.attach(10); 
}

void loop()
{
  
  xjoystick = analogRead(A1);;
  xjoystick = constrain(xjoystick, 0, 1023);
  xjoystick = map(xjoystick, 0, 1023, 0, 180);
  delay(100);
  yjoystick = analogRead(A0);;
  yjoystick = constrain(yjoystick, 0, 1023);
  yjoystick = map(yjoystick, 0, 1023, 180, 0);
  delay(100);
    Serial.print("xjoystick =  ");
    Serial.print(xjoystick);
     Serial.print("-----");
    Serial.print("yjoystick =  ");
    Serial.println(yjoystick);


  base.write(xjoystick);
  cabeca.write(yjoystick);
  
}
