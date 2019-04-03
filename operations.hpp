#include <stdio.h>
// #include <nlohmann/json.hpp>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
// #include <sys/socket.h> 
// #include <netinet/in.h> 
// #include <pthread.h>
#include <vector>

// Que implemetacion de json estamos usando
using json = nlohmann::json; 
// Standard namespace
using namespace std;

void show_users(json::array* registered_users)
{
  // print everything in the array of users
  for (int i = 0; i < registered_users.size(); i++) 
  {
    std::cout << registered_users[i] << std::endl;
  }
}

void append_user(json user, json::array* registered_users)
{
  std::cout << user << std::endl;
  // append the new user
  registered_users.push_back(user);
  // 
}

int get_user(int search_id, json::array* registered_users)
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

vector<int> get_users(vector<int>search_users, json::array* registered_users)
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
