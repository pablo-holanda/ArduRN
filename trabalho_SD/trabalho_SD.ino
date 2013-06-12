String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int local = 0;
int pwm_a = 9;
int dir_a = 8;
int posi = 0;
int led = 13;
int maior = 0;
int menor = 0;
int vetposi[2] = {0,0};
int verificar = 0;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(pwm_a, OUTPUT);
  pinMode(dir_a, OUTPUT); 
  digitalWrite(dir_a, LOW);
  pinMode(led, OUTPUT);     

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  posi = analogRead(A0);
 // velocidade(posi);
  //Controle
    if(posi>211 & posi < 632)
   {
     digitalWrite(dir_a, LOW); 
     analogWrite(pwm_a, 1010); 
   }
   else
   {
    analogWrite(pwm_a, 915); 
   }
  if (stringComplete) {
   // Serial.println(inputString); 
    local = inputString.toInt();
 switch (local)
 {
   case 1:
   menor = 0;
   maior = 41;
   parar(menor, maior);
   break;
   case 2:
   menor = 986;
   maior = 1018;
   parar(menor, maior);
   break;
   case 3:
   menor = 926;
   maior = 979;
   parar(menor, maior);
   break;
   case 4:
   menor = 890;
   maior = 919;
   parar(menor, maior);
   break;
   case 5:
   menor = 868;
   maior = 885;
   parar(menor, maior);
   break;
   case 6:
   menor = 849;
   maior = 865;
   parar(menor, maior);
   break;
   case 7:
   menor = 826;
   maior = 847;
   parar(menor, maior);
   break;
   case 8:
   menor = 751;
   maior = 804;
   parar(menor, maior);
   break;
   case 9:
   menor = 510;
   maior = 733;
   parar(menor, maior);
   break;
   case 10:
   menor = 640;
   maior = 675;
   parar(menor, maior);
   break;
   case 11:
   menor = 580;
   maior = 632;
   parar(menor, maior);
   break;
   case 12:
   menor = 532;
   maior = 566;
   parar(menor, maior);
   break;
   case 13:
   menor = 481;
   maior = 526;
   parar(menor, maior);
   break;
   case 14:
   menor = 417;
   maior = 472;
   parar(menor, maior);
   break;
   case 15:
   menor = 388;
   maior = 410;
   parar(menor, maior);
   break;
   case 16:
   menor = 328;
   maior = 382;
   parar(menor, maior);
   break;
   case 17:
   menor = 238;
   maior = 307;
   parar(menor, maior);
   break;
   case 18:
   menor = 134;
   maior = 211;
   parar(menor, maior);
   break;
   case 19:
   menor = 20;
   maior = 108;
   parar(menor, maior);
   break;
 }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
 
void parar(int posimenor, int posimaior)
{
  Serial.println("Cheguei no void");
  while(1)
  {  
     posi = analogRead(A0);
      Serial.println(posi);
     if(posi<posimaior & posi>posimenor)
     {
      digitalWrite(dir_a, HIGH);
      delay(100);
      analogWrite(pwm_a, 0); 
      Serial.println("Cheguei!!");
      for(int i = 0; i<3;i++)
      {
       digitalWrite(led, HIGH);
       delay(1000);
       digitalWrite(led, LOW);
       delay(1000);

      }
    digitalWrite(dir_a, LOW);

      digitalWrite(led, LOW);
      break;
     }
  }
  
serialEvent();

} 


 
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}




