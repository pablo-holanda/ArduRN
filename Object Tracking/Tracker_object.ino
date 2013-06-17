#include <Servo.h> 

int receive = 0;
Servo tilt;

void setup()
{
  Serial.begin(57600);
  tilt.attach(9);
  tilt.write(90);
}

void loop() {

  if (Serial.available()) {
    
    receive = Serial.parseInt() ;
    
    if(receive > 1)
    {
     tilt.write(receive);
     delay(15); 
    }
  }
 
}


