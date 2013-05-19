#include <Wire.h>
#include <Servo.h> 
#include <ArduinoNunchuk.h>

#define BAUDRATE 19200

Servo base;
Servo cabeca;

int xjoystick;
int yjoystick;
int parar;


ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup()
{ 
  Serial.begin(BAUDRATE);
  nunchuk.init();
  base.attach(9); 
  cabeca.attach(10); 
}

void loop()
{
  nunchuk.update();
  parar = nunchuk.zButton;
  if(parar == 1)
    {
  base.write(xjoystick);
  yjoystick = nunchuk.analogY;
  yjoystick = constrain(yjoystick, 34, 228);
  yjoystick = map(yjoystick, 34, 228, 0, 180);
  cabeca.write(yjoystick);
  parar = nunchuk.zButton;   
    }
    else
    {
  xjoystick = nunchuk.analogX;
  xjoystick = constrain(xjoystick, 32, 223);
  xjoystick = map(xjoystick, 32, 223, 0, 180);
  
  yjoystick = nunchuk.analogY;
  yjoystick = constrain(yjoystick, 34, 228);
  yjoystick = map(yjoystick, 34, 228, 0, 180);
    }
  
  base.write(xjoystick);
  cabeca.write(yjoystick);
  delay(10);
  
}
