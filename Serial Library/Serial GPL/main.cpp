//
//  main.cpp
//  Serial GPL
//
//  Created by Pablo Holanda on 27/09/13.
//  Copyright (c) 2013 Pablo Holanda. All rights reserved.
//

#include <iostream>
#include "SerialConfig.h"
#include "HandlingSerialRead.h"

#define SendingParameter "p"

using namespace std;


int main(int argc, const char * argv[])
{
    struct termios tio;
    struct termios stdio;
    struct termios old_stdio;
    int tty_usb;
    
    char *SerialComand = "p";
    char SerialReadTemp;
    int SerialRead = 0;
    
    SerialConfig(&stdio, &tio, &old_stdio);
    
    //openSerial(&tty_usb, &tio);
    
    
    while(1){
        
    openSerial(&tty_usb, &tio);
           
    write(tty_usb,SerialComand, BYTE_SIZE); //escreve p na porta serial
    
    read(tty_usb, &SerialReadTemp, BYTE_SIZE); //ler a porta serial

    SerialRead = HandlingIntRead(&SerialReadTemp);

    //insert code here...
    printf ("\n Leitura = %d",SerialRead);
        
            
    sleep(1);
        
    }
    return 0;
}

