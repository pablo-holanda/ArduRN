//
//  HandlingSerialRead.cpp
//  Serial GPL
//
//  Created by Pablo Holanda on 27/09/13.
//  Copyright (c) 2013 Pablo Holanda. All rights reserved.
//

#include "HandlingSerialRead.h"

int HandlingIntRead(char* gross){
    
    int tamanho = strlen(gross);
    int pos = 0;
    char saida[3] = {0,0,0};
    char vazio = ' ';
    char nl = '\n';
    char ponto = '.';
    
    for(int c = 0; c < tamanho; c++){
        
        char tmp = gross[c];
        
        if((tmp == vazio) || (tmp == nl) || (tmp == ponto) ){
            // NADA
        }else{
            saida[pos] = tmp;
            pos++;
        }
        
    }
    
    int tratada = atoi(saida);
    return tratada;
}

float HandlingFloatRead(char* gross){
    
    int tamanho = strlen(gross);
    int pos = 0;
    char saida[3] = {0,0,0};
    char vazio = ' ';
    char nl = '\n';
    char ponto = '.';
    
    
    for(int e = 0; e < tamanho; e++){
        
        char tmp4 = gross[e];
        
        if((tmp4 == vazio) || (tmp4 == nl) || (tmp4 == ponto)){
            // NADA
        }else{
            saida[pos] = tmp4;
            pos++;
        }
        
    }
    int tratada = atoi(saida);
    tratada = tratada/100;
    return tratada;
    
}