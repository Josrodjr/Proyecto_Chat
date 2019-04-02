#include <stdio.h>
#include <nlohmann/json.hpp>
#include <string>
#include <stdlib.h>
#include <iostream>

using json = nlohmann::json;
using namespace std;

json envMensaje(string contenido){
  json mensaje;
  mensaje["codigo"] = 1;
  mensaje["data"]["to"] = "halp";
  mensaje["data"]["message"] = contenido;
  //cout << mensaje.dump() << endl;
  //char resp[1024];
  //strcpy(resp, mensaje.dump().c_str()); 
  //cout << resp << endl;
  return mensaje;
}

json connect(string usuario){
  json conexion;
  conexion["codigo"] = 0;
  conexion["data"]["username"] = usuario;
  //char resp[1024];
  //strcpy(resp, conexion.dump().c_str());
  return conexion;
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

