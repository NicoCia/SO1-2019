#include "stepB.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buf[1024];

void read_stat(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/stat", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';

}

void get_cpu_times(long *user,long *system, long *idle){
    char* match;
    long basura;

    match=strstr(buf, "cpu ");

    if(match==NULL) while(1){}

    sscanf(match, "cpu  %ld %ld %ld %ld", user, &basura, system, idle);
}

long get_ctxt(){
    char* match;
    long ctxt;

    match=strstr(buf, "ctxt");

    if(match==NULL) return 0;

    sscanf(match, "ctxt %ld", &ctxt);

    return ctxt;
}

long get_processes(){
    char* match;
    long processes;

    match=strstr(buf, "processes");

    if(match==NULL) return 0;

    sscanf(match, "processes %ld", &processes);

    return processes;
}

void stepB(){
    printf("\n-------------------------PuntoB-------------------------\n");
    long user;
    long System;
    long idle;
    read_stat();
    get_cpu_times(&user,&System,&idle);
    printf("Tiempo de CPU utilizado para usuarios / sistema / procesos idle: %ld / %ld / %ld\n",user,System,idle);
    printf("Cantidad de cambios de contexto: %ld\n",get_ctxt());
    printf("Numero de procesos creados desde el inicio del sistema: %ld\n",get_processes());
}

