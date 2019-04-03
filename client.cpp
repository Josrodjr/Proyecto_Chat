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

bool corriendo = 1;

void *recibir(void *sock){
  char leer[1024];
  json recibido;
  while(corriendo){
    read(*(int*)sock, leer, 1024);
    printf("Mensaje recibido \n%s\n", leer);
    recibido = json::parse(leer);
    codeHandler(recibido);
    std::fill_n(leer, 1024, 0);
  }
  return NULL;
}

void *reseting(){
  
}

int main (int argc, char const *argv[]){
    struct sockaddr_in address; 
    int value; 
    struct sockaddr_in server_address; 
    char buffer[1024] = {0}; 
    char message[1024] = {0};
    char send[1024] = {0};
    bool conectado = 0;
    char compare[1024] = "exit\n";
    int id;
    int estado;
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
      codigo["data"]["user"]["id"] = 0;

      // TERMINA TEMPORAL

      std::fill_n(message, 1024, 0);
      std::fill_n(buffer, 1024, 0);
      std::fill_n(send, 1024, 0);

      if (codigo["code"] == 200){
        id = codigo["data"]["user"]["id"];
        // Comienzo de la escucha de mensajes
        if (pthread_create(&listen, NULL, recibir, &sock)){
          fprintf(stderr, "Error creating thread\n");
        }

        // Escritura y comienzo del menu
        int menu = 0;
        while (corriendo){
          switch (menu){
            case 0:
              printf("-----Menu de Chat-----\n");
              printf("1. Chat Global\n");
              printf("2. Chat a Usuario Unico\n");
              printf("3. Cambio de Estado\n");
              printf("4. Lista de Usuarios\n");
              printf("5. Busqueda de Usuario\n");
              printf("6. AIUDA\n");
              printf("7. Salir\n");
              printf("Ingrese su opcion\n");
              scanf("%d", &menu);
              break;

            case 1: 
              printf("Chat Global\n");
              // Escritura
              printf("Ingrese un mensaje pls \n");
              fgets(message, 1024, stdin);
              if (strcmp(message, compare)==0){
                menu = 0;
              }
              strcpy(send, envMensaje(message, "").dump().c_str());
              cout << send << endl;
              write(sock , send , strlen(send));
              std::fill_n(message, 1024, 0);
              std::fill_n(send, 1024, 0);
              break;

            case 2:
              printf("En Development");
              menu = 0;
              break;

            case 3:
              printf("Seleccione su estado\n");
              printf("0. Active\n");
              printf("1. Busy\n");
              printf("2. Inactive\n");
              scanf("%d", &estado);
              if (estado < 3 && estado >=0){
                strcpy(send, cambio_estado(id, estado).dump().c_str()); 
                write(sock, send, 1024);
              }
              else
              {
                printf("Codigo no valido\n");
              }
              menu = 0;
              break;
            
            case 4:
              printf("Lista de Usuarios");
              strcpy(send, getUser("").dump().c_str());
              write(sock, send, 1024);
              menu = 0;
              break;
            
            case 5:
              printf("Usuario Especifico");
              menu = 0;
              break;

            case 6:
              printf("Ayuda\n");
              printf("Para salir de la operacion\n que se encuentra escriba exit \n");
              menu = 0;
              break;

            case 7:
              printf("Saliendo");
              strcpy(send, goodBye().dump().c_str());
              write(sock, send, strlen(send));
              corriendo = 0;
              break; 
          
            default:
              printf("-----Menu de Chat-----\n");
              printf("1. Chat Global\n");
              printf("2. Chat a Usuario Unico\n");
              printf("3. Cambio de Estado\n");
              printf("4. Lista de Usuarios\n");
              printf("5. Busqueda de Usuario\n");
              printf("6. AIUDA\n");
              printf("7. Salir\n");
              printf("Ingrese su opcion\n");
              scanf("%d", &menu);
              break;
          }
          std::fill_n(message, 1024, 0);
          std::fill_n(send, 1024, 0);
        }
        pthread_join(listen, NULL);
      }
      if (codigo["code"] == 500){
        printf("s%\n", codigo["data"]["error_message"]);
      }
    }
    return 0;
}