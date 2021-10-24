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

void execv_comando(char comando[max]) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Erro na criacao do processo filho\n");
        exit(1);
    }
    if (pid == 0) {
        char copia[max];
        strcpy(copia, comando);
        char *token = strtok(copia, " ");
        execlp(token, comando, (char *) NULL);
    }
    if (pid > 0) {
        wait(NULL);
        return;
    }
}

void execpipe(char comando[max]) {
    char** result = 0;
    char* temp = 0;
    int tamanho = 0;
    temp = strtok(comando, "|");
    if (temp) {
        result = malloc((tamanho + 1) * sizeof (char**));
        result[tamanho++] = temp;
    }
    while ((temp = strtok(0, "|")) != 0) {
        result = realloc(result, (tamanho + 1) * sizeof (char**));
        result[tamanho++] = temp;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("%d - %s\n", i, result[i]);
    }
    int numeroDePipes = tamanho - 1;
    int des_p[2];
//    if (pipe(des_p) == -1) {
//        perror("Falha na criacao do pipe");
//        exit(1);
//    }
//    for (int i = 0; i < tamanho; i++) {
//        if (i == 0) {
//            if (fork() == 0) {
//                char *comandoSemArgumento = strtok(result[i], " ");
//                close(STDOUT_FILENO);
//                dup(des_p[WRITE_END]);
//                close(des_p[WRITE_END]);
//                close(des_p[READ_END]);
//                execlp(comandoSemArgumento, result[i], (char *) NULL);
//                perror("Falha ao executar a primeira parte do comando");
//            }
//        } else {
//            if (fork() == 0) {
//                char *comandoSemArgumento = strtok(result[i], " ");
//                close(STDIN_FILENO);
//                dup(des_p[READ_END]);
//                dup(des_p[WRITE_END]);
//                close(des_p[READ_END]);
//                close(des_p[READ_END]);
//                execlp(comandoSemArgumento, result[i], (char *) NULL);
//                perror("Falha ao executar as outras partes do comando");
//                exit(1); //se o exec der errado, fecha o processo filho B pois nÃ£o faz sentido continuar
//                  if(i == numeroDePipes){
//                     close(des_p[WRITE_END]);
//            close(des_p[READ_END]);
//            wait(NULL);
//            wait(NULL);
//                  }
//            }
//        }
//    }
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
        if (comandoComPipe == true) {
            printf("Comando com pipe. \n");
            execpipe(comando);
        } else {
            printf("Comando sem pipe. \n");
            //execv_comando(comando);
        }
        printf("\n");
    } while (strcmp(comando, "sair") != 0);
    return (0);
}

int verificaComandoPipe(char comando[max]) {
    bool comandoComPipe = false;
    if (strstr(comando, "|")) {
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



// EXEMPLOS:

//        if (fork() == 0){
//            close(STDOUT_FILENO);
//            dup(des_p[WRITE_END]);
//            close(des_p[WRITE_END]);
//            close(des_p[READ_END]);
//            execlp(copia, comando1, (char *) NULL);
//            perror("Falha ao executar a primeira parte do comando");
//            exit(1);
//        }
//    
//        if (fork() == 0){
//close(STDIN_FILENO);
//dup(des_p[READ_END]);
//close(des_p[READ_END]);
//close(des_p[WRITE_END]);
//
//char *b = strtok(comando2, "|");
//strcpy(copia, comando2);
//char *c = strtok(copia, " ");
//execlp(copia, comando2, (char *) NULL);
//perror("Falha ao executar as outras partes do comando");
//exit(1); //se o exec der errado, fecha o processo filho B pois nÃ£o faz sentido continuar
//        }
// else{
//            close(des_p[WRITE_END]);
//            close(des_p[READ_END]);
//            wait(NULL);
//            wait(NULL);
//        }
//}