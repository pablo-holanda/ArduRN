void configADC(){
ADMUX |= (1 << REFS0);    // AVCC como referencia
//64MHZ/2Khz = 80 Next = 128, 2KHZ: Necess'ario para uma boa conversao
//de acordo com o datasheet
ADCSRA|= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale
ADCSRA |= (1 << ADEN); // Enable the ADC
}

void configTempor(){
TCCR1A |= (1 << COM1A0); //Toogle OC1A/OC1B on Compare Match (Set output to low level).
//OCR1A = 8000; // 16M/2*8000 -> 16M: Cpu Clock, 2: do CTC, 8000: 8Khz de saida
TCCR1B |= (1 << WGM12) | (1 << CS10);// CTC OCR1A TOP  //No Prescale
}
