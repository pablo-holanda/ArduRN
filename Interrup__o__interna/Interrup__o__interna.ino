#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void)
{   DDRB |= 0b00000001; //Setar a PB0 como saida

    cli(); //Desabilita as interrupções globais

    OCR1A = 0x3D08; //Contar 1s, 0˜15624

    TCCR1B |= (1 << WGM12);  // Modo 4, CTC on OCR1A
   

    TIMSK1 |= (1 << OCIE1A);     //Habilita o comparador de interrupcao


    TCCR1B |= (1 << CS12) | (1 << CS10); // setar prescaler de 1024 e inicia a contagem
    
    sei();     //Habilitar as interrupcoes

    while (1);
    {
        // implemente qualquer operacao que seja
    }
}

ISR (TIMER1_COMPA_vect)  // A cada 1s essa funcao sera executada
{
  PORTB |= 0b00000001; //Nivel logico alto na porta PB0
  _delay_ms(20);      //delay de 20ms
  PORTB &= 0b00000000; //Nivel logico baixo na porta PB0
}

