#include "stepC.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char buf[2048];

void read_diskstats(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/diskstats", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';

}

void read_meminfo(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/meminfo", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';

}

void read_loadavg(){
    FILE *fp;
    size_t bytes_read;

    fp=fopen("/proc/loadavg", "r");
    bytes_read=fread(buf, 1, sizeof(buf), fp);
    fclose(fp);

    if(bytes_read==0||bytes_read==sizeof(buf)) {
        printf("Me quede sin espacio");
        return;
    }

    buf[bytes_read-1]='\0';

}

long get_diskstats(){
    char* match;
    long diskstats;

    match=strstr(buf, "sda");

    if(match==NULL){
        match=strstr(buf, "sda1");

        if(match==NULL){
            match=strstr(buf, "hda");

            if(match==NULL){
                match=strstr(buf, "hda1");

                if(match==NULL) return 0;
            }
        }
    }

    sscanf(match, "sda %ld", &diskstats);

    return diskstats;
}

long get_memtotal(){
    char* match;
    long memtotal;

    match=strstr(buf, "MemTotal");

    if(match==NULL) return 0;

    sscanf(match, "MemTotal:  %ld", &memtotal);

    return memtotal;
}

long get_memavailable(){
    char* match;
    long memavailable;

    match=strstr(buf, "MemAvailable");

    if(match==NULL) return 0;

    sscanf(match, "MemAvailable:  %ld", &memavailable);

    return memavailable;
}

double get_loadavg(){
    double loadavg;
    sscanf(buf,"%le",&loadavg);

    return loadavg;
}

void stepC(double interval, double duration){
    time_t inicial;
    time_t actual;
    inicial=time(NULL);
    actual=time(NULL);

    while(difftime(time(NULL),inicial)<=duration){
        read_diskstats();
        printf("Numero de peticiones a disco realizadas: %ld\n",get_diskstats());
        read_meminfo();
        printf("Mermoria disponible / total: %ld / %ld\n",get_memavailable(),get_memtotal());
        read_loadavg();
        printf("Promedio de carga en el ultimo minuto: %4.2f\n\n",get_loadavg());
        while(difftime(time(NULL),actual)<interval){}
        actual=time(NULL);
    }
    system("cat /proc/loadavg");
}
