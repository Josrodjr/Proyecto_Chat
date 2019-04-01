// Imports
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
// Probar para JSON
#include "json.hpp"
#include <iostream>
// Definitions
#define PORT 8080
// Que implemetacion de json estamos usando
using json = nlohmann::json;

using namespace std;

int main(int argc, char const * argv[]){

    // crear un dummy json solo para pruebas
    json user;

    user["id"] = 999;
    user["username"] = "Pepega";
    user["status"] = 2;
    user["last_connected"] = "TIME_HERE";

    std::cout << user["username"] << endl;

    // create an array of users
    json registered_users = json::array();
    // append the new user
    registered_users.push_back(user);
    // check the array
    cout << registered_users.size() << endl;
    // print everything in the array of users
    for (int i = 0; i < registered_users.size(); i++) 
    {
          std::cout << registered_users[i] << endl;
    }

    int server_file_descriptor, new_socket, value; 
    struct sockaddr_in address; 
    int address_length = sizeof(address); 
    char buffer[1024] = ""; 

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
    listen(server_file_descriptor, 5);

    // 
    while(1){
      new_socket = accept(server_file_descriptor, (struct sockaddr *) &address, (socklen_t*) &address_length);
      // Answer it works
      char *funciona = "Conectado";
      write(new_socket , funciona , strlen(funciona)); 
      int pid; 
      if ((pid  = fork()) == 0){
        // Si hay mensajes, imprimirlos
        while(read(new_socket, buffer, 1024)> 0){
          printf("Mensaje recibido \n%s\n", buffer);
          std::fill_n(buffer, 1024, 0);
        }
      }
    }
    return 0;
}