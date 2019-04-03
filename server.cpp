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

// get a mutex for the registered users
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
// user ids starting in 1
int users_id = 0;

void show_users()
{
  // print everything in the array of users
  pthread_mutex_lock(&mtx);
  for (int i = 0; i < registered_users.size(); i++) 
  {
    std::cout << registered_users[i] << endl;
  }
  pthread_mutex_unlock(&mtx);
}

void append_user(json user)
{
  // append the new user
  pthread_mutex_lock(&mtx);
  registered_users.push_back(user);
  pthread_mutex_unlock(&mtx);
}

int get_user(int search_id)
{
  pthread_mutex_lock(&mtx);
  for (int i = 0; i < registered_users.size(); i++)
  {
    if (registered_users[i]["id"] == search_id)
    {
      return registered_users[i]["id"];
    }
  }
  pthread_mutex_unlock(&mtx);
  // Not found
  return 0;
}

vector<int> get_users(vector<int>search_users)
{
  pthread_mutex_lock(&mtx);
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
  pthread_mutex_unlock(&mtx);
  return found_users;
}

void change_state(int id, int status)
{
  pthread_mutex_lock(&mtx);
  for (int i = 0; i < registered_users.size(); i++)
  {
    if (registered_users[i]["id"] == id)
    {
      // change the found value
      registered_users[i]["status"] = status;
    }
  }
  pthread_mutex_unlock(&mtx);
}

void delete_user(int id)
{
  pthread_mutex_lock(&mtx);
  for (int i = 0; i < registered_users.size(); i++)
  {
    if (registered_users[i]["id"] == id)
    {
      // change the found value
      registered_users.erase(i);
    }
  }
  pthread_mutex_unlock(&mtx);
}

void rename_user(int id, std::string new_username)
{
  pthread_mutex_lock(&mtx);
  registered_users[id]["username"] = new_username;
  pthread_mutex_unlock(&mtx);
}

void *user_request_manager(void *user_id) 
{
  // while((readBuff = read(cli->fd, buff, sizeof(buff)-1)) > 0)
  long u_id;
  u_id = (long)user_id;
  cout <<"User id: "<< u_id << endl;
  int real_userid = u_id - 1;
  cout << registered_users[real_userid] << endl;
  // read del cliente
  char buffer[1024] = ""; 
  read(registered_users[real_userid]["file_descriptor"], buffer, 1024);
  cout << "Se encontro" << buffer << endl;

  // echarle el jsonify
  json info = json::parse(buffer);
  // se supone trae un code y un data
  // cout << info["code"] << info["data"] << endl;
  // Change the name of the generic Pepega User
  if (info["code"] == 0)
  {
    cout << info["data"]["username"] << endl;
    rename_user(real_userid, info["data"]["username"]);
    // return sucess to the client
    json succ;
    succ["code"] = 200;
    succ["data"]["user"]["id"] = real_userid;
    succ["data"]["user"]["username"] = info["data"]["username"];
    succ["data"]["user"]["status"] = 0;

    write(registered_users[real_userid]["file_descriptor"], succ.dump().c_str(), succ.dump().length());
  }
  pthread_exit(NULL);
}

int main(int argc, char const * argv[]){

    // crear un dummy json solo para pruebas
    // json user;
    // user["id"] = 999;
    // user["username"] = "Pepega";
    // user["status"] = 2;
    // user["last_connected"] = "TIME_HERE";

    // append_user(user);

    // // crear un dummy json solo para pruebas
    // json user2;
    // user2["id"] = 998;
    // user2["username"] = "Pepega";
    // user2["status"] = 2;
    // user2["last_connected"] = "TIME_HERE";

    // append_user(user2);

    // show_users();

    // vector<int> test;
    // test.push_back(999);
    // test.push_back(998);
    // vector<int> result = get_users(test);
    // cout << user_ids[0] << endl;
    // for(int i=0; i<result.size(); i++)
    // {
    //   cout << result[i] << endl;
    // }

    // delete_user(999);
    // show_users();

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

      // create a new json for the newly subscribed user
      json user;
      user["id"] = users_id++;
      user["username"] = "Pepega";
      user["status"] = 0;
      user["last_connected"] = "TIME_HERE";
      user["file_descriptor"] = new_socket;

      append_user(user);

      // lanzar un user request manager thread  
      pthread_t thread;
      pthread_create(&thread, NULL, &user_request_manager, (void *) users_id);

      // if ((pid  = fork()) == 0){
      //   // Si hay mensajes, imprimirlos
      //   while(read(new_socket, buffer, 1024)> 0){
      //     printf("Mensaje recibido \n%s\n", buffer);
      //     std::fill_n(buffer, 1024, 0);

      //     // aca en buffer recibo el string que convierto en json
          
      //   }
      // }
    }
    return 0;
}