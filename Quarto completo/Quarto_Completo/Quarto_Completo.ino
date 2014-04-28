#include <IRremote.h>

//Configuracao da comunicacao IR
int RECV_PIN = 10;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

int relay[8] = {22,23,24,25,26,27,28,29};//Array com os pinos dos relays
int checkPin[8] = {0,0,0,0,0,0,0,0};//Arry para controle dos pinos digitais

void setup(){
  Serial.begin(9600);
  //Configurar os pinos de saida digital
  for(int i = 0; i < 8; i++){
    pinMode(relay[i], OUTPUT);
  }
    
  irrecv.enableIRIn();//Inicia a leitura IR
}

//Codigos raw para serem enviados pelos transmissor IR
unsigned int power[] ={4500, 4450, 550, 1700, 550, 1700, 500, 1700, 550, 600, 550, 550, 550, 550, 550, 550, 600, 550, 550, 1650, 550, 1700, 550, 1650, 550, 600, 550, 550, 550, 550, 550, 550, 600, 550, 550, 550, 550, 1700, 550, 550, 550, 600, 500, 600, 550, 550, 550, 550, 550, 600, 550, 1650, 550, 600, 550, 1650, 550, 1650, 550, 1700, 550, 1700, 550, 1650, 550, 1700, 550};             
unsigned int vol1[] ={4500, 4500, 500, 1700, 550, 1700, 500, 1700, 550, 550, 550, 600, 550, 550, 550, 550, 550, 600, 550, 1650, 550, 1700, 550, 1650, 600, 500, 600, 550, 550, 550, 600, 550, 550, 550, 550, 1700, 500, 1700, 550, 1650, 600, 550, 550, 550, 600, 500, 600, 550, 550, 550, 550, 600, 500, 600, 550, 550, 550, 1700, 550, 1650, 600, 1650, 550, 1650, 550, 1700, 550};             
unsigned int vol2[] ={4500, 4450, 550, 1700, 500, 1750, 500, 1700, 550, 550, 600, 500, 600, 550, 550, 600, 500, 550, 550, 1700, 550, 1700, 500, 1700, 550, 550, 550, 600, 550, 550, 550, 550, 550, 550, 600, 1650, 550, 1600, 650, 550, 550, 1700, 500, 600, 550, 550, 600, 500, 600, 550, 550, 550, 550, 550, 600, 1650, 550, 600, 500, 1700, 550, 1650, 550, 1700, 550, 1700, 500};             

int receiverComand[21] = {16753245,16736925,16769565,16720605,16712445,16761405,16769055,16754775,16748655,16738455,16750695,16756815,16724175,16718055,16743045,16716015,16726215,16734885,16728765,16730805,16732845}; //Array de comandos que podem ser recebidos
int ack = 0;
int posi = 0;


void pesquisa(int comando){
  for(int i = 0; i < 21; i++){
    if(comando == receiverComand[i]){
      ack = 1;
      posi = i;
      break;
    }
  }
}

void enviarComando(){
  if(posi == 0 || posi == 6 || posi == 7 ){
    switch (posi) {
      case 0: //Ligar ou desligar
        irsend.sendRaw(power, 68, 38); //Enviar o comando
        break;
      case 6://Vol -
        irsend.sendRaw(vol2, 68, 38);
        break;
      case 7://Vol +
        irsend.sendRaw(vol1, 68, 38);
        break;
    }
  irrecv.enableIRIn(); //Habilita o receptor IR novamente
  }
  
  if(posi > 11 & posi < 20){ //Comandos para ralay
    if(checkPin[posi - 12] == 0){ //Verifica se o pino está ativado ou nao
      digitalWrite(relay[posi - 12], HIGH);//Liga o pino
      checkPin[posi - 12] = 1;
    }
    else{
      digitalWrite(relay[posi - 12], LOW);//Desliga o pino
      checkPin[posi - 12] = 0;
    }
  }
}

void loop(){
  
  if(irrecv.decode(&results)){//Verifica se recebeu algum comando IR
    pesquisa(results.value);
    irrecv.resume();//Recebe o proximo valor IR
  }
  if(ack == 1){
    ack = 0;
    enviarComando();
  }
}

