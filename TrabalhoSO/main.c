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
#define max 300


/*
 * 
 */
int main(int argc, char** argv) {
    char comando[max];
    do{
        printf("Digite o comando: ");
        gets(comando);
        printf("\n");
    } while (strcmp(comando,"sair") != 0);
    return(0);
}

