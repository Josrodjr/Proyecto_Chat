### Proyecto Chat

## Utilizacion
Server
```
g++ -o server server.cpp -lpthread
./server
```
En otra consola o dispositivo (Cliente)
```
g++ -o client client.cpp -lpthread
./client <USERNAME>
```

## Cliente

- [x] Chateo con usuarios
- [x] Chateo Privado con multithreading y multiprocessing (se uso PTHREADS)
- [x] Cambio de status
- [ ] Listado de usuarios e informacion de usuarios (sin probar)

## Server

- [x] Atencion con multithreading (PTHREADS revisar funcion User_request_manager)
- [x] Broadcasting y mensajes directos
- [x] Registro de usuarios
- [ ] Liberacion de usuarios
- [x] Manejo de status
- [x] Respuesta a solicitud de usuarios

## Status = (0: active, 1: busy, 2: inactive)
```
user:{
 id: number,
 username: string,
 status: 0,
 last_connected: time,
}
```

## Request connection
```
{
 code: 0,
 data:{
   username: string,
 }
}
```

## SUCCESS
```
{
 code: 200,
 data: {
   user:{
     id: number,
     username: string,
     status: 0,
   }
 }
}
```

## ERROR
```
{
 code: 500,
 data: {
   error_message: string,
 }
}
```

## Send message
```
{
 code: 1,
 data: {
   to: List<id>,
   message: string,
   file_type:? string,
 }
}
```

## Receive message
```
{
 code: 201,
 data: {
   from: username,
   message: string,
 }
}
```

## GET user
```
{
 code: 3,
 data:{
   user: List<id>,
 }
}
```

## Recieve user
```
{
 code: 203,
 data: {
   users: List<Users>,
 }
}
```

## Change status
```
{
 code: 4,
 data: {
   user: id,
   new_status: number,
 }
}
```

## Change status success
```
{
 code: 204,
 data: {},
}
```
## Goodbye 
```
{
 code: 5,
 data: {},
}
```