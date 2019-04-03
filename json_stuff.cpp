#include <stdio.h>
#include <nlohmann/json.hpp>
#include <string>
#include <stdlib.h>
#include <iostream>

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

json envMensaje(string contenido){
  json mensaje;
  mensaje["codigo"] = 1;
  mensaje["data"]["to"] = "halp";
  mensaje["data"]["message"] = contenido;
  return mensaje;
}

json cambio_estado(int id, int estado){
  json status;
  status["code"] = 4;
  status["data"]["user"] = id;
  status["data"]["new_status"] = estado;
  return status;
}



void codeHandler(json envio){
  printf("halp Pls");
  int codigo = envio["codigo"];
  printf("%d \n", codigo);
  switch (codigo){
    case 0:
      printf("Esta intentando conectar");
      break;
  
    default:
      break;
  }
}

