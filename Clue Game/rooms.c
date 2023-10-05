#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms.h"
#include "items.h"

// Allocates memory to create a Room struct and initializes its fields
struct Room* create_room(char* name){
   struct Room *newRoom = (struct Room*)malloc(sizeof(struct Room));
   newRoom->north = NULL;
   newRoom->south = NULL;
   newRoom->east = NULL;
   newRoom->west = NULL;
   newRoom->itemList = NULL;
   newRoom->name = name;
   for(int i = 0; i < 5; i++){
     newRoom->characters[i] = (char*) malloc(sizeof(char));
   }   
   return newRoom;
}

// Prints out the surrounding rooms of curRoom if they're not NULL
void room_dir(struct Room* curRoom){
   // Prints out the name of the room to the north if it's not NULL
   if(curRoom->north != NULL){
     printf("North: %s\n", curRoom->north->name);
   }
   // Prints out the name of the room to the south if it's not NULL
   if(curRoom->south != NULL){
     printf("South: %s\n", curRoom->south->name);
   }
   // Prints out the name of the room to the east if it's not NULL
   if(curRoom->east != NULL){
     printf("East: %s\n", curRoom->east->name);
   }
   // Prints out the name of the room to the west if it's not NULL
   if(curRoom->west != NULL){
     printf("West: %s\n", curRoom->west->name);
   }
}

// Prints out the list of characters in curRoom
void room_chars(struct Room* curRoom){
   printf("Characters: ");
   for(int i = 0; i < 5; i++){
      printf("%s ", curRoom->characters[i]);
   }
   printf("\n");
}

// Prints out the itemList of curRoom
void room_items(struct Room *curRoom){
   // traverse is set to the head of curRoom's Item linked list
   struct Item *traverse = curRoom->itemList;
   printf("Items: ");
   while(traverse != NULL){
      printf("%s ", traverse->name);
      traverse = traverse->next;
   }
   printf("\n");
}

// Creates the game board and links the rooms together
void create_gameboard(struct Room** rooms){
   // Assigns the rooms's north and west pointers
   for(int i = 8; i>=0; i--){
       if(i % 3 == 0){
         rooms[i]->west = NULL;
       }
       if((i - 3) < 0){
         rooms[i]->north = NULL;
       }
       if(i % 3 != 0){
          rooms[i]->west = rooms[i - 1];
       } 
       if((i - 3) >= 0){
          rooms[i]->north = rooms[i - 3];
       }
   }
   // Assigns the room's south and east pointers
   for(int i = 0; i < 8; i++){
      if((i + 3) <= 8){
         rooms[i]->south = rooms[i+3];
      }
      if((i + 3) > 8){
         rooms[i]->south = NULL;
      }
      if((i + 1) % 3 == 0){
         rooms[i]->east = NULL;
      }
      if((i + 1) % 3 != 0){
        rooms[i]->east = rooms[i+1];
      }
   }
}

// Insert items randomly into game board
void item_insert(struct Item **items, struct Room **rooms){
   srand(time(NULL)); 
   int j = 0; 
   for(int i = 0; i < 6; i++){
      do{
         j = rand() % 9;
      }while(rooms[j]->itemList != NULL);
      add_item(items[i], &rooms[j]->itemList);
   }
}

// Insert characters randomly into game board
void char_insert(char **characterNames, struct Room **rooms){
   srand(time(NULL));
   int j = 0;
   for(int i = 0; i < 5; i++){
      do {
         j = rand() % 9; 
      } while(strcmp(rooms[j]->characters[0], "") != 0);
      if (rooms[j]->characters[0] == NULL){
        rooms[j]->characters[0] = strdup(characterNames[i]);  
      }
   }
}
