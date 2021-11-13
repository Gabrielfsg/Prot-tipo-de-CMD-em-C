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

    int des_p[2];
    int des_p2[2];
    pid_t a;
    pid_t b;

    if (pipe(des_p) == -1) {
        perror("Falha na criacao do pipe");
        exit(1);
    }
    if (pipe(des_p2) == -1) {
        perror("Falha na criacao do pipe");
        exit(1);
    }

    if (((a = fork()) == -1)) {
        perror("Falha na criaÃ§Ã£o do fork xd! \n");
        exit(1);
    } else if (a == 0) {
        close(STDOUT_FILENO);
        dup(des_p[WRITE_END]);
        close(des_p[WRITE_END]);
        close(des_p[READ_END]);
        char comandoSemArgumento[max];
        strcpy(comandoSemArgumento, result[0]);
        char** result2 = 0;
        char* temp2 = 0;
        int tamanho2 = 0;
        temp2 = strtok(comandoSemArgumento, " ");
        if (temp2) {
            result2 = malloc((tamanho2 + 1) * sizeof (char**));
            result2[tamanho2++] = temp2;
        }
        while ((temp2 = strtok(0, " ")) != 0) {
            result2 = realloc(result2, (tamanho2 + 1) * sizeof (char**));
            result2[tamanho2++] = temp2;
        }
        if (tamanho2 == 1) {
            execlp(result2[0], result2[0], (char *) 0);
        } else {
            execlp(result2[0], result2[0], result2[1], 0);
        }
    }
    int wstatus;
    int i = 1;
    waitpid(a, &wstatus, WUNTRACED);
    tamanho -= 1;
    while (tamanho != 0) {
        if (((b = fork()) == -1)) {
            perror("Falha na criaÃ§Ã£o do fork xd! \n");
            exit(1);
        }
        if (b == 0) {
            close(STDIN_FILENO);
            dup(des_p[READ_END]);
            close(des_p[WRITE_END]);
            close(des_p[READ_END]);
            
            if((tamanho -1) != 0){
                close(STDOUT_FILENO);
                dup(des_p2[WRITE_END]);
                close(des_p2[WRITE_END]);
                close(des_p2[READ_END]);
            }
            
            char comandoSemArgumento[max];
            strcpy(comandoSemArgumento, result[i]);
            char** result2 = 0;
            char* temp2 = 0;
            int tamanho2 = 0;
            temp2 = strtok(comandoSemArgumento, " ");
            if (temp2) {
                result2 = malloc((tamanho2 + 1) * sizeof (char**));
                result2[tamanho2++] = temp2;
            }
            while ((temp2 = strtok(0, " ")) != 0) {
                result2 = realloc(result2, (tamanho2 + 1) * sizeof (char**));
                result2[tamanho2++] = temp2;
            }
            if (tamanho2 == 1) {
                execlp(result2[0], result2[0], (char *) 0);
            } else {
                execlp(result2[0], result2[0], result2[1], 0);
            }
        }
        close(des_p[WRITE_END]);
        close(des_p[READ_END]);

        if (pipe(des_p) == -1) {
        perror("Falha na criacao do pipe");
        exit(1);
        }

        waitpid(b, &wstatus, WUNTRACED);
        i++;
        tamanho--;
        if (tamanho == 0) {
            break;
        }
        if (((a = fork()) == -1)) {
            perror("Falha na criaÃ§Ã£o do fork xd! \n");
            exit(1);
        } else if (a == 0) {
            close(STDIN_FILENO);
            dup(des_p2[READ_END]);
            close(des_p2[WRITE_END]);
            close(des_p2[READ_END]);

            if((tamanho -1) != 0){
                close(STDOUT_FILENO);
                dup(des_p[WRITE_END]);
                close(des_p[WRITE_END]);
                close(des_p[READ_END]);
            }
            
            char comandoSemArgumento[max];
            strcpy(comandoSemArgumento, result[i]);
            char** result2 = 0;
            char* temp2 = 0;
            int tamanho2 = 0;
            temp2 = strtok(comandoSemArgumento, " ");
            if (temp2) {
                result2 = malloc((tamanho2 + 1) * sizeof (char**));
                result2[tamanho2++] = temp2;
            }
            while ((temp2 = strtok(0, " ")) != 0) {
                result2 = realloc(result2, (tamanho2 + 1) * sizeof (char**));
                result2[tamanho2++] = temp2;
            }
            if (tamanho2 == 1) {
                execlp(result2[0], result2[0], (char *) 0);
            } else {
                execlp(result2[0], result2[0], result2[1], 0);
            }
        }
        close(des_p2[WRITE_END]);
        close(des_p2[READ_END]);
        
        if (pipe(des_p2) == -1) {
            perror("Falha na criacao do pipe");
            exit(1);
        }

        waitpid(a, &wstatus, WUNTRACED);
        i++;
        tamanho--;
    }
}

int main(int argc, char** argv) {
    char comando[max];
    bool comandoComPipe = false;
    printf("Simulador Terminal. Para sair digite (sair) \n");
    do {
        printf("Digite o comando: ");
        gets(comando);
        comandoComPipe = verificaComandoPipe(comando);
        if (comandoComPipe == true) {
            execpipe(comando);
        } else {
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