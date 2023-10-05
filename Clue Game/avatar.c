#include <string.h>
#include <stdlib.h>
#include "items.h"
#include "avatar.h"

// Allocates memory to create a new avatar struct
struct Avatar* create_player(char* name){
   struct Avatar* p1 = (struct Avatar*)malloc(sizeof(struct Avatar));
   p1-> name= name; 
   p1->inventory = NULL;
   p1->location = NULL;
   return p1;
}

// Print out the avatars's inventory
void inventory(struct Avatar* player){
   // Head of the player's Item linked list
   struct Item* traverse = player->inventory;
   printf("Inventory: ");
   while(traverse != NULL){
      // Prints each item in the inventory
      printf("%s,", traverse->name);
      // Traverses to the next item in the inventory
      traverse = traverse->next;
   }
   printf("\n");
}

// Allows avatar to take an item from the room they're currently in
int take(char *itemName, struct Avatar *avatar){
   // Sets the currentRoom to the avatar's location
   struct Room *currentRoom = avatar->location;

   // Sets traverse to the head of the room's Item linked list
   struct Item *traverse = currentRoom->itemList;
 
   int len = strlen(itemName);
   if((len > 0) && (itemName[len-1] == '\n')){
     itemName[len - 1] = '\0';
   }
   while(traverse != NULL){
     // Drops the item from the room and adds it to the avatar's inventory if there's a match
     if(strcmp(traverse->name, itemName) == 0){
        drop_item(traverse, &(currentRoom->itemList));
        add_item(traverse, &(avatar->inventory));
        return 0;
     }
     // Traverses to the next item in the room if there isn't a match
     traverse = traverse->next;
   }
   return -1;
}

// Allows avatar to drop an item from their inventory
int drop(char *itemName, struct Avatar *avatar){
   // Sets the currentRoom to the avatar's location
   struct Room *currentRoom = avatar->location;

   // Sets traverse to the head of the avatar's inventory
   struct Item *traverse = avatar->inventory;
   int len = strlen(itemName);
   if((len > 0) && (itemName[len - 1] == '\n')){
     itemName[len - 1]='\0';
   } 
   while(traverse != NULL){
      // If there's a match, drop the item from the avatar's inventory and add it to the room's Item linked list
      if(strcmp(traverse->name, itemName) == 0){
        drop_item(traverse, &(avatar->inventory));
        add_item(traverse, &(currentRoom->itemList));
        return 0;
      }
      // Traverse to the next item in the avatar's inventory if there isn't a match
      traverse = traverse->next;
   }
   return -1;
}

// Allows avatar to look at current room's information
void look(struct Avatar* avatar){ 
   printf("\n[You are in the %s", avatar->location->name);
   printf("]\n");
   room_items(avatar->location);
   room_chars(avatar->location);
   room_dir(avatar->location);
   printf("\n");
}

// Moves avatar in a given direction
int move_player(struct Avatar *avatar, char *direction){
   int len = strlen(direction);
   if((len > 0) && (direction[len - 1] == '\n')){
      direction[len - 1] = '\0';
   }
   // If the given direction is north, check the room to the north of the avatar's current location
   if(strcmp("north", direction) == 0){
      // If the room to the north is NULL, return 1
      if(avatar->location->north == NULL){
        printf("There is no room to the north, please choose another direction\n");
        return 1;
      }
      // If the room to the north is not NULL, set the avatar's location to the room to the north
      avatar->location = avatar->location->north;
      return 0;
   }
   // If the given direction is south, check the room to the south of the avatar's current location
   else if(strcmp("south", direction) == 0){
      // If the room to the south is NULL, return 1
      if(avatar->location->south == NULL){
        printf("There is no room to the south, please choose another direction\n");
        return 1;
      }
      // If the room to the south is not NULL, set the avatar's location to the room to the south
      avatar->location = avatar->location->south;
      return 0;
   }
   // If the given direction is west, check the room to the west of the avatar's current location
   else if(strcmp("west", direction) == 0){
      // If the room to the west is NULL, return 1
      if(avatar->location->west == NULL){
         printf("There is no room to the west, please choose another direction\n");
         return 1;
      }
      // If the room to the west is not NULL, set the avatar's location to the room to the west
      avatar->location = avatar->location->west;
      return 0;
   }
   // If the given direction is east, check the room to the east of the avatar's current location
   else if(strcmp("east", direction) == 0){
      // If the room to the east is NULL, return 1
      if(avatar->location->east == NULL){
         printf("There is no room to the east, please choose another direction\n");
         return 1;
      }
      // If the room to the east is not NULL, set the avatar's location to the room to the east
      avatar->location = avatar->location->east;
      return 0;
   }
   // If the given direction is not one of the valid options
   else{
      printf("Room direction invalid\n");
      return 1;
   }
}

