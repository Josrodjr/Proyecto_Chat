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
  return conexion;
}

// Agregar lista de ids
json envMensaje(string contenido, int usuario){
  json mensaje;
  vector<int>usuarios_vector;
  if (usuario != -1){
    usuarios_vector.push_back(usuario);
  }
  // usuarios_vector.push_back(0);
  mensaje["code"] = 1;
  mensaje["data"]["to"] = usuarios_vector;
  mensaje["data"]["message"] = contenido;
  return mensaje;
}

json getUser(int ids){
  json users;
  vector<int>usuarios_vector;
  if (ids != -1){
    usuarios_vector.push_back(ids);
  }
  users["code"] = 3;
  users["data"]["user"] = usuarios_vector;
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
  long codigo = (long)envio["code"];
  switch (codigo){
    // Exito de Conexion
    case 200:
      //printf("Esta intentando conectar");
      break;
    
    // Errores
    case 500:
      printf("%s", envio["data"]["error_message"]);
      fflush(stdout);
      break;
    
    // Mensaje recibido 
    case 201:
      printf("%s:\n", envio["data"]["from"]);
      printf("%s\n", envio["data"]["message"]);
      fflush(stdout);
      break;

    // Exito de Cambio de estado
    case 204:
      printf("Cambio exitoso");
      fflush(stdout);
      break;
    
    // Usuario Recibido
    case 203:{
      printf("User Recieved");
      json recibidos = json::array();
      recibidos = envio["data"]["users"];
      int i = 0;
      for (i; i <= (int)sizeof(recibidos)/sizeof(recibidos[0]); i++){
        printf("%s", recibidos[i]["username"]);
        fflush(stdout);
        printf("  %s\n", recibidos[i]["id"]);
        fflush(stdout);
      }
      fflush(stdout);
      break;
    }
      
  
    default:
      printf("Respuesta Default");
      fflush(stdout);
  }
}

