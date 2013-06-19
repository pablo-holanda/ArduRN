#define F_CPU 16000000UL

#include <avr/io.h>

#include <util/delay.h>

#define BAUDRATE 9600

#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)


void USART_init(void);

unsigned char USART_RECEBER(void);

void USART_EVIAR( unsigned char data);
 
char leitura;



int main(void){

   USART_init();        //Chamada para a configuracao da comunicacao

  int start = 1;
     
      //Char destinado para Armazenar a leitura!

	while(1){        //loo infinito

                if(start == 1)
                {
                
                  USART_ENVIAR('A');
                  
                  start = 0;
                  
                }
                //chamada de funcao para leitura de dado
                  
                leitura = USART_RECEBER();
 		
                 //chamada de funcao para enviar o dado recebido
                  
                  USART_ENVIAR('A');
               
 		_delay_ms(10);        	//Delay de 10ms
 	}



return 0;

}

void USART_init(void){


// configuracao do baud rate #9600

UBRR0L = (uint8_t)(BAUD_PRESCALLER);
UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
 
/*
    * Modo Asynchronous
    
    * Sem Paridade
    
    * 1 StopBit
    
    * Tamanho do Char igual a 8
*/
 
UCSR0C = ((3<<UCSZ00));

//Habilitar leitura e escrita

UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}



unsigned char USART_RECEBER(void){

//aguarda ate que algo seja recebi!
 while(!(UCSR0A & (1<<RXC0)));

//retorna a leitura que esta armazenada no buffer
 return UDR0;



}


void USART_ENVIAR( unsigned char data){


//aguarda ate que toda informacao seja enviada
 while(!(UCSR0A & (1<<UDRE0)));

 UDR0 = data;

}


