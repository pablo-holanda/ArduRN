#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <util/delay.h>

uint16_t adc_value;  //Variavel para armazenar o valor do ADC

uint8_t pwm = 0;  //Variavel para a normalizacao do ADC para PWM

void adc_init(void); //Funcao para inicializar o ADC

uint16_t read_adc(uint8_t channel);   	//Funcao para ler o ADC

int main(void){
  
    DDRD = 0b11111111;     //setar PORTD como saida
    PORTD = 0x00;
    TCCR0A = 0b10100011; //Fast PWM de 8bits,
    TCCR0B = 0b00000011; // Prescaler de 64
    TCNT0 = 0;           // Resetar o TCNT0
    OCR0A = 0;           // Valor inicial da saida PWM

        adc_init();    //Configurar o ADC

	while(1){       //loop infinito

 			adc_value = read_adc(0);        	//ler o ADC
 
                        pwm = ceil(adc_value * (255 / 1023.0)); //normalizacao da leitura do ADC para o intervalo de 0˜255 para poder aplicar no PWM
                        OCR0A = pwm;
 			_delay_ms(20);                	//delay de 500ms
	}
return 0;

}

void adc_init(void){

 ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));  //16Mhz/128 = 125Khz referencia de clock do ADC

 ADMUX |= (1<<REFS0);                			//referencia do Avcc (5V)

 ADCSRA |= (1<<ADEN);                			//ativar o ADC

 ADCSRA |= (1<<ADSC);                			//Fazer a primeira conversao pois ela e a mais lenta e assim quando eu chamar uma leitura do ADC tudo estara funcionando.

}

uint16_t read_adc(uint8_t channel){

 ADMUX &= 0xF0;                    	//limpar o canal de leitura

 ADMUX |= channel;                	//definir o canal do ADC

 ADCSRA |= (1<<ADSC);               //iniciar uma nova conversao

 while(ADCSRA & (1<<ADSC));         //espera ate que a conversao acabe

 return ADCW;                   	//retorna a leitura do ADC

}
