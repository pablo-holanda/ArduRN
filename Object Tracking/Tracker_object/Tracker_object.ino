#include <Servo.h> 

int receive = 0;
Servo tilt;
Servo pan;


void setup()
{
  Serial.begin(57600);
  tilt.attach(10);
  pan.attach(11);
  tilt.write(50);
  pan.write(80);
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


