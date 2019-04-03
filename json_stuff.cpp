#include <stdio.h>
#include <nlohmann/json.hpp>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using namespace std;

// Metodos para el cliente

json connect(string usuario){
  json conexion;
  conexion["code"] = 0;
  conexion["data"]["username"] = usuario;
  //char resp[1024];
  //strcpy(resp, conexion.dump().c_str());
  return conexion;
}

// Agregar lista de ids
json envMensaje(string contenido, string usuarios){
  json mensaje, to;
  vector<int>usuarios_vector;
  to.push_back(usuarios_vector);
  mensaje["code"] = 1;
  mensaje["data"]["to"] = to;
  mensaje["data"]["message"] = contenido;
  return mensaje;
}

json getUser(string usuarios){
  json users;
  users["code"] = 3;
  users["data"]["user"] = usuarios;
  return users;
}

json cambio_estado(int id, int estado){
  json status;
  status["code"] = 4;
  status["data"]["user"] = id;
  status["data"]["new_status"] = estado;
  return status;
}

json goodBye(){
  json adios;
  adios["code"] = 5;
  adios["data"] = "";
  return adios;
}



void codeHandler(json envio){
  int codigo = envio["code"];
  printf("%d \n", codigo);
  switch (codigo){
    // Exito de Conexion
    case 200:
      //printf("Esta intentando conectar");
      break;
    
    // Errores
    case 500:
      printf("s%", envio["data"]["error_message"]);
      break;
    
    // Mensaje recibido 
    case 201:
      printf("s%:\n", envio["data"]["from"]);
      printf("s%\n", envio["data"]["message"]);
      break;

    // Exito de Cambio de estado
    case 204:
      printf("Cambio exitoso");
      break;
    
    // Usuario Recibido
    case 203:
      printf("User Recieved");
      break;
  
    default:
      break;
  }
}

