uint16_t x[N];                    

// Parâmetros 
int32_t b1[N]={0.25,0.25,0.25,0.25};

uint16_t a;
uint16_t i;

void InitADC()                    
{
ADMUX=(1<<REFS0); 
ADMUX&=~((1<<REFS1)|(1<<ADLAR)|(1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));                      
ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); 
}

uint16_t LerADC(uint8_t ch)      // função para ler o adc
{
   ch=ch&0b00000111;
   ADMUX|=ch;
   ADCSRA|=(1<<ADSC);
   while(!(ADCSRA & (1<<ADIF)));
   //_delay_ms(1000);
   ADCSRA|=(1<<ADIF);
   return(ADC);
}
void setup()          //configuração do adc e comunicação 
{
DDRC=0x00;            //PORTC as INPUT
DDRD=0xFF;            //PORTD is OUTPUT
DDRD=0xFF;
for(i=0;i<N;i++)
  {
    InitADC();
    a=LerADC(4);
    x[i]=a;
  }
  Serial.begin(9600);
}

int32_t num1=0,num2=0,num3=0,y1[M],y2[M],y3[M],sum1=0,sum2=0,sum3=0,ans1=0,ans2=0,ans3=0;    // variáveis para determinar a saida 

void loop()            
{
  for(int i=0;i<M;i++)
  {
    num1=0;                 
    num2=0;                 
    num3=0;                 
    for(int j=0;j<N;j++)     
    {
      InitADC();
      x[j]=LerADC(4);
    }
    for(int k=0;k<N;k++)   //convolução
    {
      num1+=b1[k]*x[N-1-k];        //filtro1
      num2+=b2[k]*x[N-1-k];        //filtro2
      num3+=b3[k]*x[N-1-k];        //filtro3
    }
    
    y1[i]=num1/10000;              //normalixação
    y2[i]=num2/10000;
    y3[i]=num3/10000;    
  }
    
  //valores emRMS
  for(int i=0;i<M;i++)
  {
    sum1+=y1[i]*y1[i];
    sum2+=y2[i]*y2[i];
    sum3+=y3[i]*y3[i];
  }
  sum1/=M;
  sum2/=M;
  sum3/=M;
  ans1=sqrt(sum1);
  ans2=sqrt(sum2);
  ans3=sqrt(sum3);
  
  // imprimir os valores na serial
  Serial.print("200-600Hz::");
  Serial.println(ans1);
  Serial.print("600-1200Hz::");
  Serial.println(ans2);
  Serial.print("1200-2400Hz::");
  Serial.println(ans3);
  
  dacx(ans1);
  dacy(ans2);
}

void dacx(unsigned char a)             
{
  byte k=0;
   for(unsigned char i=0;i<2;i++)
    {
      k=a&(1<<i);
      if(k)
      PORTB|=(1<<i);
      else
      PORTB&=~(1<<i);      
    }
   for(unsigned char i=0;i<6;i++)
    {
      k=a&(1<<(i+2));
      if(k)
      PORTD|=(1<<(7-i));
      else
      PORTD&=~(1<<(7-i));     
    }
} 

void dacy(unsigned char a)             
{
  byte k=0;
  for(unsigned char i=0;i<4;i++)
    {
      k=a&(1<<i);
      if(k)
      PORTC|=(1<<(3-i));
      else
      PORTC&=~(1<<(3-i));     
    }
  for(unsigned char i=0;i<4;i++)
    {
      k=a&(1<<(i+4));
      if(k)
      PORTB|=(1<<(5-i));
      else
      PORTB&=~(1<<(5-i));
    }
}

