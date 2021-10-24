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
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#define max 300

void execv_comando(char comando[max]){
    pid_t pid;
    pid = fork();
    if(pid<0){
        perror("Erro na criacao do processo filho\n");
        exit(1);
    }
    if(pid == 0){
        int ret;
        char copia[max];
        strcpy(copia, comando);
        char *token = strtok(comando, " ");
        execlp(token, copia, (char *) NULL);
    }
    if(pid > 0){
        wait(NULL);
        return;
    }
}

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
            execv_comando(comando);
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
