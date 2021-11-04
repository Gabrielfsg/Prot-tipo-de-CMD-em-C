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
#include <assert.h>
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
        printf("Comando: %s\n", comando);
        printf("copia: %s\n", copia);
        printf("token: %s\n", token);

        char** result = 0;
        char* temp = 0;
        int tamanho = 0;
        temp = strtok(comando, " ");
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
        if (tamanho == 1) {
            execlp(result[0], result[0], (char *) NULL);
        } else {
            execlp(result[0], result[0], result[1], 0);
        }
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


//    printf("tamanho: %d \n",tamanho);
//    int numeroDePipes = tamanho - 1;
//    
//    int des_p[2];
//    if (pipe(des_p) == -1) {
//        perror("Falha na criacao do pipe");
//        exit(1);
//    }
    for (int i = 0; i < tamanho; i++) {
//
//        if (fork() == 0) {
//            printf("%d etapa. \n", i);
//            char comandoSemArgumento[max];
//            printf("%s comando. \n", result[i]);
//            strcpy(comandoSemArgumento, result[i]);
//            char** result2 = 0;
//            char* temp2 = 0;
//            int tamanho2 = 0;
//            temp2 = strtok(comandoSemArgumento, " ");
//            if (temp2) {
//                result2 = malloc((tamanho2 + 1) * sizeof (char**));
//                result2[tamanho2++] = temp2;
//            }
//            while ((temp2 = strtok(0, " ")) != 0) {
//                result2 = realloc(result2, (tamanho2 + 1) * sizeof (char**));
//                result2[tamanho2++] = temp2;
//            }
//            
//            if (i == 0) {
//                close(STDOUT_FILENO);
//                dup(des_p[WRITE_END]);
//                close(des_p[WRITE_END]);
//                close(des_p[READ_END]);
//            } else if (i = tamanho - 1) {
//                close(STDIN_FILENO);
//                dup(des_p[READ_END]);
//                close(des_p[READ_END]);
//                close(des_p[READ_END]);
//            } else {
//                close(STDIN_FILENO);
//                dup(des_p[READ_END]);
//                dup(des_p[WRITE_END]);
//                close(des_p[READ_END]);
//                close(des_p[READ_END]);
//            }
//            if (tamanho2 == 1) {
//                execlp(result2[0], result2[0], (char *) NULL);
//            } else {
//                execlp(result[0], result[0], result[1], 0);
//            }
//            printf("Falha ao executar o %d ° comando", i);
//        }
//
//
//        if (i == tamanho - 1) {
//            close(des_p[WRITE_END]);
//            close(des_p[READ_END]);
//            wait(NULL);
//            wait(NULL);
//        }
    }
}

void pipeline(char ***cmd) {
    int fd[2];
    pid_t pid;
    int fdd = 0;

    while (*cmd != NULL) {
        pipe(fd);
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            dup2(fdd, 0);
            if (*(cmd + 1) != NULL) {
                dup2(fd[1], 1);
            }
            close(fd[0]);
            execvp((*cmd)[0], *cmd);
            exit(1);
        } else {
            wait(NULL);
            close(fd[1]);
            fdd = fd[0];
            cmd++;
        }
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
        if (comandoComPipe == true) {
            printf("Comando com pipe. \n");
            execpipe(comando);
        } else {
            printf("Comando sem pipe. \n");
            execv_comando(comando);
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

