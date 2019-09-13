#include "stepA.h"
#include "stepB.h"
#include "stepC.h"
#include "stepD.h"
#include <stdio.h>
#include <stdlib.h>

const char* program_name;
void controlar_doble_Argumentos(int argc,char* argv[]);
void imprimir_argumentos_validos(FILE* stream, int exit_code){
    fprintf(stream,"Error: %s opciones:\n",program_name);
    fprintf(stream,
            "-s     Imprime informacion adicional\n"
            "-l     Imprime informacion extra sobre memoria.\n"
            "-p     Imprime informacion sobre los files descriptors del proceso.\n"
            "-f     Imprime de los limites de archivos abierto del proceso\n"
            "-t     Imprime el kernel stack trace del proceso\n");
    exit(exit_code);
}

int main(int argc,char *argv[]){
    program_name = argv[0];
    controlar_doble_Argumentos(argc,argv);
    char aux=argv[1];
    switch (aux) {
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
            imprimir_argumentos_validos();
            abort();
        }
    }
}

void controlarArgumentos(int argc,char* argv[]){
    //Lista argumentos validos si se pasa por parámetro más de un argumento
    if(argc>4||argv[2]=='s'||argv[2]=='l'||argv[2]=='p'||argv[2]=='f'||argv[2]=='t')    imprimir_argumentos_validos();

}
