// Libs
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
// Probar para JSON
#include <nlohmann/json.hpp> 
#include "json_stuff.cpp"
// Definiciones
#define PORT 8080 

void *recibir(void *sock){
  char leer[1024];
  json recibido;
  while(1){
    read(*(int*)sock, leer, 1024);
    printf("Mensaje recibido \n%s\n", leer);
    recibido = json::parse(leer);
    
    std::fill_n(leer, 1024, 0);
  }
  return NULL;
}

int main (int argc, char const *argv[]){
    struct sockaddr_in address; 
    int value; 
    struct sockaddr_in server_address; 
    char buffer[1024] = {0}; 
    char message[1024] = {0};
    char send[1024] = {0};
    bool conectado = 0;
    pthread_t listen;

    int sock = 0;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_address, '0', sizeof(server_address)); 

    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(PORT); 

    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // Conexion al server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address))== 0){
      value = read( sock , buffer, 1024); 
      printf("%s\n",buffer );
      std::fill_n(buffer, 1024, 0);

      // Pregunta de Nombre de Usuario
      strcpy(send, connect(argv[1]).dump().c_str());
      write(sock, send, strlen(send));

      /*
      read(sock, buffer, 1024);
      json codigo = json::parse(buffer);
      */
      // TEMPORAL
      json codigo;
      codigo["code"] = 200;

      // TERMINA TEMPORAL

      std::fill_n(message, 1024, 0);
      std::fill_n(buffer, 1024, 0);
      std::fill_n(send, 1024, 0);

      if (codigo["code"] == 200){

        // Comienzo de la escucha de mensajes
          if (pthread_create(&listen, NULL, recibir, &sock)){
          fprintf(stderr, "Error creating thread\n");
        }

        // Escritura y comienzo del menu
        while (1){
          printf("Ingrese un mensaje pls \n");
          fgets(message, 1024, stdin);
          strcpy(send, envMensaje(message).dump().c_str());
          cout << send << endl;
          write(sock , send , strlen(send));
          std::fill_n(message, 1024, 0);
          std::fill_n(send, 1024, 0);
        }
        pthread_join(listen, NULL);
      }
    }
    return 0;
}