// Libs
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// Probar para JSON
#include "json.hpp"
// Definiciones
#define PORT 8080 

int main (int argc, char const *argv[]){
    struct sockaddr_in address; 
    int value; 
    struct sockaddr_in server_address; 
    char buffer[1024] = {0}; 
    char message[1024] = {0};

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
      while (1){      
        printf("Ingrese un mensaje pls \n");
        fgets(message, 1024, stdin);
        write(sock , message , strlen(message));
        std::fill_n(message, 1024, 0);

        /*
        while(value > 0){
          printf("Mensaje recibido \n%s\n", buffer);
          std::fill_n(buffer, 1024, 0);
        }*/
      }
    }
    return 0;
}