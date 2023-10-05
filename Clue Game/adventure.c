#include <stdio.h>
#include <time.h>
#include <string.h>
#include "rooms.h"
#include "items.h"
#include "avatar.h"
#include "clue.h"

// TEST: ensures gameboard has been constructed correctly
void listObjects(struct Room **gameboard){
   for(int i = 0; i < 9; i++){
      printf("[%s]\n", gameboard[i]->name); 
      if(gameboard[i]->north != NULL){
         printf("North: %s\n", gameboard[i]->north->name);
      }
      else{
         printf("North: NULL\n");
      }
      if(gameboard[i]->south != NULL){
         printf("South: %s\n", gameboard[i]->south->name);
      }
      else{
         printf("South: NULL\n");
      }
      if(gameboard[i]->east != NULL){
         printf("East: %s\n", gameboard[i]->east->name);
      }
      else{
         printf("East: NULL\n");
      }
      if(gameboard[i]->west != NULL){
         printf("West: %s\n", gameboard[i]->west->name);
      }
      else{
         printf("West: NULL\n");
      }
      room_chars(gameboard[i]);
      room_items(gameboard[i]);
      printf("\n\n");
   } 
}

// Lists rooms, items, and characters in the game 
void list(struct Room **rooms, struct Item **items, char** characters){
   printf("\n[Rooms]\n");
   for(int i = 0; i < 9; i++){
     printf("%s\n", rooms[i]->name);
   }
   printf("\n[Items]\n");
   for(int i = 0; i < 6; i ++){
     printf("%s\n", items[i]->name);
   }
   printf("\n[Characters]\n");
   for(int i = 0; i < 5; i++){
     printf("%s\n", characters[i]);
   }
   printf("\n");
}

// Randomizes room names
void randomize_rooms(char **roomNames){
   int j;
   char *temp;
   srand(time(NULL));
   
   for(int i = 8; i > 0; i--){
       j = rand() % (i + 1);
       temp = roomNames[j];
       roomNames[j] = roomNames[i];
       roomNames[i] = temp;
   }
}

// Randomizes characters
void randomize_characters(char** players){
   int j;
   char *temp;
   srand(time(NULL));
   for(int i = 4; i > 0; i--){
      j = rand() % (i + 1);
      temp = players[j];
      players[j] = players[i];
      players[i] = temp;
   }
}

// Randomizes items
void randomize_items(char** items){
   srand(time(NULL));
   int j;
   char *temp;
   for(int i = 5; i > 0; i--){
      j = rand() % (i + 1);
     temp = items[j];
     items[j] = items[i];
     items[i] = temp;
   }
}

int main(int argc, char *argv[]){
   // Creates an array of 9 room names
   char *roomNames[9] = {"kitchen", "ballroom", "conservatory room", "billiard room", "library", "lounge", "hall",
   "study", "dining room"};
   randomize_rooms(roomNames);
   // Creates an array of Room pointers
   struct Room* rooms[9];
   for(int i = 0; i < 9; i++){
      rooms[i] = create_room(roomNames[i]);
      printf("%s\n", rooms[i]->name);
   }
   printf("\n");

   // Creates an array of 6 item names
   char *itemNames[6] = {"candlestick", "dagger", "lead pipe", "revolver", "rope", "wrench"};
   randomize_items(itemNames);
   // Creates an array of Item pointers
   struct Item* items[6];
   for(int i = 0; i < 6; i++){
      items[i] = create_item(itemNames[i]);
      printf("%s\n", items[i]->name); 
   }
   printf("\n");

   // Creates an array of character names
   char *characterNames[5] = {"Miss Scarlet", "Colonel Mustard", "Mrs. White", "The Reverend Green",
   "Professor Plum"};
   randomize_characters(characterNames);
   for(int i = 0; i < 5; i++){
     printf("%s\n", characterNames[i]);
   }

   // Creates game board and inserts the items and characters randomly into the rooms
   create_gameboard(rooms);
   item_insert(items, rooms);
   char_insert(characterNames, rooms);
   printf("\n");
   listObjects(rooms);

   // Randomize game solution
   struct Clue* answer = create_answer(characterNames, items, rooms);
   printf("Murderer: %s\n", answer->murderer);
   printf("Weapon: %s\n", answer->weapon->name);
   printf("Crime Scene: %s\n", answer->room->name);
   
   // Place avatar into a random room
   int avatarSpawn = 0;
   do {
      avatarSpawn = rand() % 9;
   } while(strcmp(rooms[avatarSpawn]->characters[0], "") != 0);
   struct Avatar* player = create_player("avatar");
   player->location = rooms[avatarSpawn];
   printf("Player has spawned at %s\n---\n\n", rooms[avatarSpawn]->name);
  
   // Game implementation
   printf("Welcome to Clue! Type help for commands\n\n");
   int playerWon = 0;
   int clueCount = 0;
   do{
      char playerInput[15];
      printf("$"); 
      fgets(playerInput, sizeof(playerInput), stdin); 
   if(strcmp(playerInput, "help\n") == 0) {
      printf("help: show list of commands\n");
      printf("list: show list of items, rooms, and characters\n");
      printf("look: show list of characters, surrounding rooms, current location, and items in the room you are in\n");
      printf("go: allows you to move your avatar north, south, east, or west\n");
      printf("take: allows you to take an item in the current room you're in\n");
      printf("drop: allows you to drop an item in your inventory\n");
      printf("inventory: lists the items in your inventory\n");
      printf("clue: allows you to make a guess on who is the murderer, the weapon used, as well as the crime scene location.\n");
      printf("To win, make a correct guess about the crime details within 10 tries\n");
    }
    else if(strcmp(playerInput, "list\n") == 0){
      list(rooms, items, characterNames);
    }
    else if(strcmp(playerInput, "look\n") == 0){
      look(player);
    }
    else if(strcmp(playerInput, "go\n") == 0){
      int success = 1;
      while(success!=0){
        char dir[10];
        printf("Direction: ");
        fgets(dir, sizeof(dir), stdin);
        success = move_player(player, dir);
        if(success = 0){
           printf("Player is now in %s\n", player->location->name);
        }
      }
    }
    else if(strcmp(playerInput, "take\n") == 0){
       if(player->location->itemList == NULL){
         printf("There are no items in this room to take\n");
       }
       else{
          int success = -1;
          do {
             char item[20]; 
             printf("Item: ");
             fgets(item,sizeof(item),stdin);
             success = take(item, player);
             if(success == -1){
               printf("Item not found, please choose another item\n");
             }
          } while(success == -1);
       }
    }
    else if(strcmp(playerInput, "drop\n") == 0){
       char item[15];
        if(player->inventory == NULL){
          printf("You don't have any inventory items to drop. Please choose another command.\n");
        }
        printf("Item: ");
        fgets(item, sizeof(item), stdin);
        drop(item, player);
    }
    else if(strcmp(playerInput, "inventory\n") == 0){
        inventory(player);
    }
    else if(strcmp(playerInput, "clue\n") == 0){
      if(player->inventory != NULL || player->location->itemList != NULL){
        char character[20];
        char weapon[20];
        int validChar = 0;
        int len = 0;
        do {
          printf("Character: ");
          fgets(character, sizeof(character), stdin);
          len = strlen(character);
          if((len > 0) && character[len - 1] == '\n'){
            character[len-1]='\0';
          }
          for(int i = 0; i < 5; i++){
            if(strcmp(characterNames[i], character) == 0){
              validChar = 1;
              break;
            }
          }
          if(validChar == 0){
            printf("Character name invalid. Please choose another character\n");
          }
       } while(validChar == 0);
       int validItem = 0;
       do {
          printf("Weapon: ");
          fgets(weapon, sizeof(weapon), stdin);
          len = strlen(weapon);
          if((len > 0) && weapon[len-1] == '\n'){
            weapon[len-1] = '\0';
          }
          struct Item* traverse = player->inventory;
          while(traverse!=NULL){
            if(strcmp(traverse->name, weapon)==0){
              validItem = 1;
              break;
            }
            traverse = traverse->next;
          }
          if(validItem != 1){ 
            traverse = player->location->itemList;
            while(traverse != NULL){
              if(strcmp(traverse->name, weapon) == 0){
                validItem = 1;
                break; 
              }
              traverse = traverse->next;
            } 
          }
          if(validItem == 0){
            printf("Item name is not in inventory or room. Please choose another item\n");
          }
       } while(validItem == 0); 
       int guess = clue(answer, rooms, player, character, weapon);
       clueCount++;
       if(guess == 3){
         playerWon = 1;
         printf("Congrats, you won!\n");
       }
       else{
         printf("You did not guess all 3 elements correctly\n");
       }
     }
     else{
       printf("There are no valid items. Please choose another command\n");
     }
   }
   else if(strcmp(playerInput, "quit\n") == 0){
     playerWon = 1;
     break;
   }
   else{
     printf("Command not found\n");
   }
  } while(playerWon != 1 || clueCount != 10);   
}

