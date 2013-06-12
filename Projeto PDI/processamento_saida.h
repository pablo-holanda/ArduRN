//
//  processamento_saida.h
//  ELA Home Care
//
//  Created by Pablo Holanda on 09/01/13.
//  Copyright (c) 2013 Pablo Holanda. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>

using namespace std;




//#####################################
// VARIAVEIS GLOBAIS
//#####################################



//#####################################


//#####################################
// PARAMETRO FUGA
//#####################################
int concatSaidaFuga(char* fuga){
    
    int tamFuga = strlen(fuga);
    int pos = 0;
    char saidaFuga[2] = {0,0};
    char vazio = ' ';
    char nl = '\n';
    
    for(int c = 0; c < tamFuga; c++){
        
        char tmp = fuga[c];
        
        if((tmp == vazio) || (tmp == nl)){
            // NADA
        }else{
            saidaFuga[pos] = tmp;
            pos++;
        }
        
    }
    
    int fulga = atoi(saidaFuga);
    return fulga;
    
}


//#####################################
// PARAMETRO: VC ESTIMADO
//#####################################


int concatSaidaVc(char* vc){
    
    int tamVc = strlen(vc);
    int pos4 = 0;
    char saidaVc[3] = {0,0,0};
    char vazio4 = ' ';
    char nl4 = '\n';
    char ponto = '.';
    
    
    for(int e = 0; e < tamVc; e++){
        
        char tmp4 = vc[e];
        
        if((tmp4 == vazio4) || (tmp4 == nl4) || (tmp4 == ponto)){
            // NADA
            //cout << "Pri!" << endl;
        }else{
            saidaVc[pos4] = tmp4;
            pos4++;
        }
        
    }
    int num = atoi(saidaVc);
    
    return num;
}


//#####################################
// PARAMETRO: FR TOTAL
//#####################################

int concatSaidaFr(char* fr){
    
    int tamFr = strlen(fr);
    int pos3 = 0;
    char saidaFr[2] = {0,0};
    char vazio3 = ' ';
    char nl3 = '\n';
    
    for(int d = 0; d < tamFr; d++){
        
        char tmp3 = fr[d];
        
        if((tmp3 == vazio3) || (tmp3 == nl3)){
            // NADA
            //cout << "Pri!" << endl;
        }else{
            saidaFr[pos3] = tmp3;
            //cout << "" << endl;
            pos3++;
        }
        
    }
    int num2 = atoi(saidaFr);
    
    return num2;
}


//#####################################
// PARAMETRO: RELACAO I:E  PT01
//#####################################

int proRelI(char* ri){
    
    int tamRi = strlen(ri);
    int pos4 = 0;
    char saidaRi[2] = {0,0};
    char vazio4 = ' ';
    char nl4 = '\n';
    char ponto = '.';
    
    for(int f = 0; f < tamRi; f++){
        
        char tmp4 = ri[f];
        
        if((tmp4 == vazio4) || (tmp4 == nl4) || (tmp4 == ponto)){
            // NADA
            //cout << "Pri!" << endl;
        }else{
            saidaRi[pos4] = tmp4;
            //cout << "tm: " << saidaRi[pos4] << endl;
            pos4++;
        }
        
    }
    
    int num3 = atoi(saidaRi);
    
    return num3;
}


//#####################################
// PARAMETRO: RELACAO I:E  PT02
//#####################################

int proRelE(char* re){
    
    int tamRe = strlen(re);
    int pos5 = 0;
    char saidaRe[2] = {0,0};
    char vazio5 = ' ';
    char nl5 = '\n';
    char ponto = '.';
    
    for(int g = 0; g < tamRe; g++){
        
        char tmp5 = re[g];
        
        if((tmp5 == vazio5) || (tmp5 == nl5) || (tmp5 == ponto)){
            // NADA
            //cout << "Pri!" << endl;
        }else{
            saidaRe[pos5] = tmp5;
            //cout << "tm: " << saidaRi[pos4] << endl;
            pos5++;
        }
        
    }
    
    int num4 = atoi(saidaRe);
    
    return num4;
}
