#include "stepA.h"
#include "stepB.h"
#include "stepC.h"
#include "stepD.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

const char* program_name;

void controlar_doble_Argumentos(int argc,char* argv[]);

void imprimir_argumentos_validos(FILE* stream, int exit_code){
    fprintf(stream,"Error: %s opciones:\n",program_name);
    fprintf(stream,
            "-s     Imprime informacion adicional\n"
            "-l     Imprime informacion extra sobre memoria. Requiere 2 parametros.\n"
            "-p     Imprime informacion sobre los files descriptors del proceso. Requiere un pid como parametro.\n"
            "-f     Imprime de los limites de archivos abierto del proceso.Requiere un pid como parametro.\n"
            "-t     Imprime el kernel stack trace del proceso.Requiere un pid como parametro.\n");
    exit(exit_code);
}

int main(int argc,char *argv[]){
    program_name = argv[0];
    controlar_doble_Argumentos(argc,argv);
    if(argc==1)stepA();

    switch (getopt(argc,argv,"slp:ft")) {
        case 's':
            stepA();
            stepB();
            break;
        case 'l':
            stepA();
            stepB();
            stepC(argv[2],argv[3]);
            break;
        case 'p':
            stepA();
            stepB();
            stepD('p',atoi(argv[2]));
            break;
        case 'f':
            stepA();
            stepB();
            stepD('f',atoi(argv[2]));
            break;
        case 't':
            stepA();
            stepB();
            stepD('t',atoi(argv[2]));
            break;
        case -1:
            break;
        default:
            imprimir_argumentos_validos(stdout,0);
            abort();
    }
}

void controlar_doble_Argumentos(int argc,char* argv[]){
    //Lista argumentos validos si se pasa por parámetro más de un argumento
    if(argc>2) {
        if(strncmp(argv[1],"-s",3)==0&&argv[2]==NULL)return;
        if(argc==4&&(strncmp(argv[1],"-l",4)==0&&argv[4]==NULL))return;
        if(argc==3&&(strncmp(argv[1],"-p",4)==0&&argv[3]==NULL))return;
        if(argc==3&&(strncmp(argv[1],"-f",4)==0&&argv[3]==NULL))return;
        if(argc==3&&(strncmp(argv[1],"-t",4)==0&&argv[3]==NULL))return;
        imprimir_argumentos_validos(stdout,0);
    }
}
