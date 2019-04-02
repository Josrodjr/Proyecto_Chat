// Imports
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>
// Probar para JSON
#include "json.hpp"
#include <iostream>
#include <vector>
// Definitions
#define PORT 8080
// Que implemetacion de json estamos usando
using json = nlohmann::json; 
// Standard namespace
using namespace std;
// create an array of users GLOBAL SCOPE
json registered_users = json::array();

void show_users()
{
  // print everything in the array of users
  for (int i = 0; i < registered_users.size(); i++) 
  {
    std::cout << registered_users[i] << endl;
  }
}

void append_user(json user)
{
  // append the new user
  registered_users.push_back(user);
}

int get_user(int search_id)
{
  for (int i = 0; i < registered_users.size(); i++)
  {
    if (registered_users[i]["id"] == search_id)
    {
      return registered_users[i]["id"];
    }
  }
  // Not found
  return 0;
}

vector<int> get_users(vector<int>search_users)
{

  vector<int>found_users;
  // for each element in the search user prop 
  for (int j = 0; j < search_users.size(); j++)
  {
    // for each element in the registered users DB array
    for (int i = 0; i < registered_users.size(); i++)
    {
      if (registered_users[i]["id"] == search_users[j])
      {
        // append the found values
        found_users.push_back(registered_users[i]["id"]);
      }
    }
  }
  return found_users;
}

int main(int argc, char const * argv[]){

    // crear un dummy json solo para pruebas
    json user;
    user["id"] = 999;
    user["username"] = "Pepega";
    user["status"] = 2;
    user["last_connected"] = "TIME_HERE";

    append_user(user);

    // crear un dummy json solo para pruebas
    json user2;
    user2["id"] = 998;
    user2["username"] = "Pepega";
    user2["status"] = 2;
    user2["last_connected"] = "TIME_HERE";

    append_user(user2);

    show_users();

    vector<int> test;
    test.push_back(999);
    test.push_back(998);

    // cout << test[0] << test[1] << endl;

    vector<int> result = get_users(test);
    // cout << user_ids[0] << endl;
    for(int i=0; i<result.size(); i++)
    {
      cout << result[i] << endl;
    }
    // std::cout << user["username"] << endl;

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
      char *funciona = "Conectado, ingrese su nombre de usuario";
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