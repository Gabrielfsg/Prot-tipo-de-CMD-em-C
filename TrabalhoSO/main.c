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
#define READ_END 0
#define WRITE_END 1
void execv_comando(char comando[max]){
    pid_t pid;
    pid = fork();
    if(pid<0){
        perror("Erro na criacao do processo filho\n");
        exit(1);
    }
    if(pid == 0){
        char copia[max];
        strcpy(copia, comando);
        char *token = strtok(copia, " ");
        execlp(token, comando, (char *) NULL);
    }
    if(pid > 0){
        wait(NULL);
        return;
    }
}

void execpipe(char comando[max]) {
    int des_p[2];
    char comando1[max], comando2[max], copia[max];
    strcpy(comando1, comando);
    strcpy(comando2, comando);
    char *token = strtok(comando1, "|");
    strcpy(copia, comando1);
    char *a = strtok(copia, " ");
    return;
    if (pipe(des_p) == -1) {
        perror("Falha na criacao do pipe");
        exit(1);
    }
    if (fork() == 0){
        close(STDOUT_FILENO);
        dup(des_p[WRITE_END]);
        close(des_p[WRITE_END]);
        close(des_p[READ_END]);
        execlp(copia, comando1, (char *) NULL);
        perror("Falha ao executar a primeira parte do comando");
        exit(1);
    }

    if (fork() == 0){
        close(STDIN_FILENO);
        dup(des_p[READ_END]);
        close(des_p[READ_END]);
        close(des_p[WRITE_END]);
        
        char *b = strtok(comando2, "|");
        strcpy(copia, comando2);
        char *c = strtok(copia, " ");
        execlp(copia, comando2, (char *) NULL);
        perror("Falha ao executar as outras partes do comando");
        exit(1); //se o exec der errado, fecha o processo filho B pois nÃ£o faz sentido continuar
    }
    else{
        close(des_p[WRITE_END]);
        close(des_p[READ_END]);
        wait(NULL);
        wait(NULL);
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
            execpipe(comando);
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