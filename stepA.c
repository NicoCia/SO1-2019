#include "stepA.h"
#include <stdio.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <stdlib.h>

char buf[1024];

void read_hostname(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/sys/kernel/hostname", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';
}

void read_cpuinfo(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/cpuinfo", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read]='\0';
}

void read_kernel_version(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/sys/kernel/version", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';
}

void read_filesystem(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/filesystems", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';
}

void get_cpu_type(char *cpu_type){
    char* match;

    match=strstr(buf, "vendor_id");

    if(match==NULL) return;

    sscanf(match, "vendor_id : %s", cpu_type);

}

void get_cpu_model(){
    char aux[1024];
    char* match1;
    char* match2;
    unsigned long posicion1;
    unsigned long posicion2;

    match1=strstr(buf, "name");
    match2=strstr(buf, "stepping");
    if(match1==NULL||match2==NULL) return ;
    posicion1=strlen(buf)-strlen(match1)+6;
    posicion2=strlen(buf)-strlen(match2)-1;
    for(unsigned long i=posicion1; i<posicion2; i++){
        aux[i-posicion1]=buf[i];
    }

    strcpy(buf,aux);
}

void get_filesystem(){
    char aux[1024];
    int j=0;
    for(unsigned long i=6; i<strlen(buf); i++){
        if(buf[i]=='\n') {
            if(buf[i+1]=='n')i+=6;
            else i++;
        }
        aux[j]=buf[i];
        j++;
    }
    aux[j]='\0';
    strcpy(buf,aux);
}

void stepA() {
    char aux[1024]="";
    read_hostname();
    puts(buf);
    //printf("Fecha y hora actual: ");
    system("date");
    read_cpuinfo();
    get_cpu_type(aux);
    printf("Tipo de CPU: %s \n", aux);
    printf("Modelo de CPU: ");
    get_cpu_model();
    puts(buf);
    read_kernel_version();
    printf("Version de kernel: ");
    puts(buf);
    const long minute=60;
    const long hour=minute*60;
    const long day=hour*24;
    struct sysinfo si;
    sysinfo(&si);
    printf("system uptime : %ld days, %ld:%02ld:%02ld \n",si.uptime/day,(si.uptime%day)/hour, (si.uptime%hour)/minute, si.uptime%minute );
    read_filesystem();
    get_filesystem();
    printf("Sistemas de archivos soportados: ");
    puts(buf);

}