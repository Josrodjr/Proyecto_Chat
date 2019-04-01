// Imports
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
// Probar para JSON
#include "json.hpp"
// Definitions
#define PORT 8080

int main(int argc, char const * argv[]){
    int server_file_descriptor, new_socket, value; 
    struct sockaddr_in address; 
    int address_length = sizeof(address); 
    char buffer[1024] = {0}; 

    // Crear el file descriptor del socket
    server_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    // Agregar el socket al puerto OPCIONAL
    // int opt = 1; 
    // setsockopt(server_file_descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // Agregar al struct parametros
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 

    // Agregar el socket al nuevo puerto numerado
    bind(server_file_descriptor, (struct sockaddr *) &address, sizeof(address));

    // oir en el puerto
    listen(server_file_descriptor, 3);

    // 
    new_socket = accept(server_file_descriptor, (struct sockaddr *) &address, (socklen_t*) &address_length);

    // leer lo que encontramos
    value = read( new_socket , buffer, 1024); 

    // Answer it works
    char *funciona = "Conectado";
    send(new_socket , funciona , strlen(funciona) , 0 ); 

    return 0;
}