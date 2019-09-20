#include "stepD.h"
#include <stdio.h>
#include <string.h>

char buf1[1024]="";
char buf2[1024]="";

void pDp(int pid){
    FILE *fp=popen("echo $USER","r");
    size_t bytes_read=fread(buf1,1, sizeof(buf1),fp);
    pclose(fp);
    buf1[bytes_read-1]='\0';
    int esp=strlen(buf1)*2+18;
    int j=0;
    int conta=0;

    snprintf(buf2,64,"ls -l /proc/%i/fd",pid);
    fp=popen(buf2,"r");
    bytes_read=fread(buf1,1, sizeof(buf1),fp);
    pclose(fp);
    buf1[bytes_read-1]='\0';

    for(int i=0; i<strlen(buf1); i++){
        if(conta==14) i+=esp;
        if(buf1[i]=='\n') conta=0;
        buf2[j]=buf1[i];
        j++;
        conta++;
    }
    buf2[j]='\0';
    puts(buf2);
}

void pDf(int pid){
    long softLimit;
    long hardLimit;
    char* match;

    snprintf(buf2,64,"/proc/%i/limits",pid);
    FILE *fp=fopen(buf2,"r");
    size_t bytes_read=fread(buf1,1, sizeof(buf1),fp);
    fclose(fp);
    buf1[bytes_read-1]='\0';
    match=strstr(buf1, "Max open files");

    if(match==NULL) printf("me rompi");

    sscanf(match, "Max open files %ld %ld",&softLimit,&hardLimit);
    printf("Limites de archivos abiertos (Soft Limit/Hard Limit): %ld / %ld\n", softLimit,hardLimit);
}

void pDt(int pid){
    snprintf(buf2,64,"sudo cat /proc/%i/stack",pid);
    FILE *fp=popen(buf2,"r");
    size_t bytes_read=fread(buf1,1, sizeof(buf1),fp);
    pclose(fp);
    buf1[bytes_read-1]='\0';
    puts(buf1);
}

void stepD(char opt, int pid){
    printf("\n-------------------------PuntoD-------------------------\n");
    switch(opt){
        case('p'): pDp(pid); break;
        case('f'): pDf(pid); break;
        case('t'): pDt(pid); break;
        default: break;
    }
}
