Proyecto_Chat

### Status = (0: active, 1: busy, 2: inactive)
```
user:{
 id: number,
 username: string,
 status: 0,
 last_connected: time,
}
```

### Request connection
```
{
 code: 0,
 data:{
   username: string,
 }
}
```

### SUCCESS
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

### ERROR
```
{
 code: 500,
 data: {
   error_message: string,
 }
}
```

### Send message
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

### Receive message
```
{
 code: 201,
 data: {
   from: username,
   message: string,
 }
}
```

### GET user
```
{
 code: 3,
 data:{
   user: List<id>,
 }
}
```

### Recieve user
```
{
 code: 203,
 data: {
   users: List<Users>,
 }
}
```

### Change status
```
{
 code: 4,
 data: {
   user: id,
   new_status: number,
 }
}
```

### Change status success
```
{
 code: 204,
 data: {},
}
```
### Goodbye (va a ser later bitch.)

mis notas
```
cd mnt/c/Users/Josro/Documents/GitHub/Proyecto_Chat
g++ -o server server.cpp
sudo apt install nlohmann-json-dev
```