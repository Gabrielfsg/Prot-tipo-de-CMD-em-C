/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: gabriel f
 *
 * Created on 17 de outubro de 2021, 20:39
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 300

/*
 * 
 */
int main(int argc, char** argv) {
    char comando[max];
    bool comandoComPipe = false;
    printf("Simulador Terminal. Para sair digite (sair) \n");
    do {
        printf("Digite o comando: ");
        gets(comando);
        comandoComPipe = verificaComandoPipe(comando);
        if(comandoComPipe == true){
            printf("Comando com pipe. \n");
        } else{
            printf("Comando sem pipe. \n");
        }
        printf("\n");
    } while (strcmp(comando, "sair") != 0);
    return (0);
}

int verificaComandoPipe(char comando[max]) {
    bool comandoComPipe = false;
        if(strstr(comando, "|")){
            comandoComPipe = true;
            return comandoComPipe;
        } else {
            return comandoComPipe;
        }
}

int contaCaracteres(char string[max]) {
    int cont = strlen(string);
    return cont;
}