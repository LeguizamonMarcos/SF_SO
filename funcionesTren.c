
/**
 * TRABAJO PRACTICO
 * #SISTEMAS OPERATIVOS#
 * PROF.: ALEJANDRO MOSTOVOI
 * ALUMNOS:
 * Amado Pablo
 * Leguizamon Marcos
 * Juan Ramasco
 * /
 
 /** 
 * Manejo de tren
 * 
 * funciones del tren
 * Manejos de los mensajes de la estructura tren cliente
 */ 
#include <stdbool.h>
#include "tren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80


void createTren(ST_TREN * tren){
     
     memset(tren->idTren,'\0',8);
     memset(tren->estacionOrigen,'\0',strlen(tren->estacionOrigen));
     memset(tren->estacionDestino,'\0',strlen(tren->estacionDestino));
     memset(tren->pasajeros,'\0',strlen(tren->pasajeros));
     tren->combustible=0;
     tren->tViaje=0;
     strcpy(tren->estado,"estacion");//estacion,anden, transito
     memset(tren->motivo ,'\0',strlen(tren->motivo));//PASO O ANDEN
     
}

void obtenerPalabra (const char* linea, char * palabra, int *indice){
    int i=0;
    while(*linea && *linea!=',' && *linea!='.'){
        *(palabra+i)=*linea;
        linea++;
        *indice=*indice+1;
        i++;
    }
    *indice=*indice+1;
}

void cargarTren(const char* linea,ST_TREN * tren){
     int i=0;
     int indice=0;
     char * palabra=(char*)malloc(sizeof(char)*MAX);

     while(*linea!='\0'){
            i++;
            indice=0;
            memset(palabra,'\0',MAX);
            obtenerPalabra(linea,palabra,&indice);
            
            if(i==1){
                strcpy(tren->idTren,palabra);
            }
            if(i==2){
                strcpy(tren->estacionOrigen,palabra);
            }
             if(i==3){
                 strcpy(tren->estacionDestino,palabra);
            }
             if(i==4){
                strcpy(tren->pasajeros,palabra);
            }
             if(i==5){
                tren->combustible=atoi(palabra);
            }
             if(i==6){
                tren->tViaje=atoi(palabra);
            }
             if(i==7){
                strcpy(tren->estado,palabra);
            }
             if(i==8){
                strcpy(tren->motivo,palabra);
            }
        linea=linea+indice;          
     }
    
}

void itoa(char *linea,int valor){
    sprintf(linea,"%d",valor); 
}

void enviarTren(ST_TREN * tren, int sockTren){

    char * mensaje=(char*)malloc(sizeof(char)*MAX);
	codificarMsj(mensaje,tren);
    send(sockTren, mensaje, sizeof(mensaje),0); 
    free(mensaje);
}
void concatenarMsj (char *buffer,char *aux, char* msj, char * coma){
    
    strcpy(aux,msj);
    strcat(buffer,aux);
    strcat(buffer,coma);
}

 void codificarMsj (char * buffer, ST_TREN * tren){
    int i=0;
    char coma[2];
    char tipoEnt[2];
    memset(coma,'\0',2);
    memset(tipoEnt,'\0',2);
    tipoEnt[0]='T';
    coma[0]=',';
    char * aux=(char*)malloc(sizeof(char)*MAX); 
    memset(aux,'\0',MAX);

    strcpy(aux,tipoEnt);
    strcpy(buffer,aux);
    strcat(buffer,coma);
    printf("linea:%s \n",buffer);
    
    while(i<8){
        memset(aux,'\0',MAX);

        switch(i){
           
            case 0:
                    concatenarMsj(buffer,aux,tren->idTren,coma);
                    
                    break;
            case 1:
                    concatenarMsj(buffer,aux, tren->estacionOrigen,coma);
                    
                    break;
            case 2:
                    concatenarMsj(buffer,aux,tren->estacionDestino,coma);
                    
                    break;
            case 3:
                    concatenarMsj(buffer,aux,tren->pasajeros,coma); 
                             
                    break;
            case 4:
                    itoa(aux,tren->combustible);
                    strcat(buffer,aux);
                    strcat(buffer,coma);
                    
                    break;
            case 5:
                    itoa(aux,tren->tViaje);
                    strcat(buffer,aux);
                    strcat(buffer,coma);
                    
                    break;
            case 6:
                    concatenarMsj(buffer,aux,tren->estado,coma); 
                    
                    break;
            case 7:
                    concatenarMsj(buffer,aux,tren->motivo,coma);
                    break;    
            default:  
                    break;
        }

        i++;
    }
}

void escribirMensaje(int sockTren,ST_TREN * tren) { 
    char mensaje[MAX]; 
    int i; 
    for (;;) { 
        bzero(mensaje, sizeof(mensaje)); 
        printf(" \n Ingrese el mensaje: \n"); 
        i = 0; 
        while ((mensaje[i++] = getchar()) != '\n'); 
        
            if ((strncmp(mensaje, "info", 4)) == 0) { 
                printf("Informacion del tren:\n"); 
                printf("Modelo:%s\n",tren->idTren);
                printf("Origen:%s\n",tren->estacionOrigen);
                printf("Destino:%s\n",tren->estacionDestino);
                printf("Cant de pasajeros:%s\n",tren->pasajeros);
                printf("Litros de combustible:%d\n",tren->combustible);
                printf("tiempo de viaje restante:%d\n",tren->tViaje);
                printf("Estado:%s\n",tren->estado); // en transito, en anden, en estacion
                printf("Motivo:%s\n",tren->motivo); // paso o anden
          } 
        if ((strncmp(mensaje, "enviar tren", 4)) == 0) { 
                printf("El tren se  esta poniendo en marcha.\n"); 
                enviarTren(tren, sockTren);

            break; 
        }

            if ((strncmp(mensaje, "exit", 4)) == 0) { 
            printf("te desconectaste.\n"); 
            break; 
        } else{
        
            send(sockTren, mensaje, sizeof(mensaje),0); 
            //bzero(mensaje, sizeof(mensaje)); 
            //recv(sockTren, mensaje, sizeof(mensaje),0); 
           // printf("Estacion envio: %s \n", mensaje); 
        } 
        bzero(mensaje, sizeof(mensaje)); 
    } 
} 
 
