#include "clue.h"
#include "items.h"
#include "rooms.h"
#include "avatar.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

// Allocates memory to create a Clue struct and initializes its fields
struct Clue* create_answer(char **characters, struct Item** itemList, struct Room **roomList){
   struct Clue *answer = (struct Clue*)malloc(sizeof(struct Clue));
   srand(time(NULL));
   int i = rand() % 9; 
   int j = rand() % 6;
   int k = rand() % 5;
   answer->weapon = itemList[j];
   answer->room = roomList[j];
   answer->murderer = characters[k];
   return answer;
}
//Allows user to guess answer
int clue(struct Clue *answer, struct Room **rooms, struct Avatar *avatar, char *character, char *item){
   // Sets the avatarRoom to the avatar's current location
   struct Room *avatarRoom = avatar->location;
   int correctGuess = 0;
   // Iterates through the 9 rooms and 5 characters
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 5; j++){
         // If the room's character is not NULL and the character is in the current room, set the room's character to an empty string
         if(rooms[i]->characters[j] != NULL && strcmp(rooms[i]->characters[j], character) == 0){
            strcpy(rooms[i]->characters[j], "");
               // Iterates through the 6 items
	       for(int k = 0; k < 6; k++){
               // If there isn't a character in the avatar's room, then copy the character into the avatar's room
               if(avatarRoom->characters[k] == NULL){
                  strcpy(avatarRoom->characters[k], character);
                  break;
               }
            }
         }
      }
   }
   // If the avatar's location is the same name as the answer's room, increment correctGuess
   if(strcmp(avatar->location->name, answer->room->name)==0){
      printf("Room match\n");
      correctGuess++;
   }
   // If the character matches the answer's murderer, increment correctGuess
   if(strcmp(character, answer->murderer) == 0){
      printf("Character match\n");
      correctGuess++;
   }
   // If the item matches the answer's weapon, increment correctGuess
   if(strcmp(item, answer->weapon->name) == 0){
      printf("Item match\n");
      correctGuess++;
      return correctGuess;
   }
   return correctGuess;
}
