/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
int UD = 0;
int LR = 0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  LR = analogRead(A0);
  LR = constrain(LR, 466, 525);
  LR = map(LR, 466, 525, 0, 4);
  UD = analogRead(A5);
  UD = constrain(UD, 132, 915);
  UD = map(UD, 132, 915, 0, 4);

  
  
  
  if(LR == 0){
  Serial.print('L');
  delay(50);
  }
  
  if(LR == 4){
   Serial.print('R');
   delay(50);
  }
  
  if(UD == 0){
   Serial.print('D');
   delay(50);
  }
  
  if(UD == 4){
   Serial.print('U');
   delay(50);
  }       // delay in between reads for stability
  
  if(UD == 1 & LR == 1)
  {
    
   Serial.print('S');
   delay(50);
  
  }
  
   if(UD == 2 & LR == 2)
  {
    
   Serial.print('S');
   delay(50);
  
  }
   if(UD == 3 & LR == 3)
  {
    
   Serial.print('S');
   delay(50);
  
  }
     if(UD == 3 & LR == 1)
  {
    
   Serial.print('S');
   delay(50);
  
  }
     if(UD == 3 & LR == 2)
  {
    
   Serial.print('S');
   delay(50);
  
  }
     if(UD == 2 & LR == 3)
  {
    
   Serial.print('S');
   delay(50);
  
  }
     if(UD == 1 & LR == 3)
  {
    
   Serial.print('S');
   delay(50);
  
  }
}
