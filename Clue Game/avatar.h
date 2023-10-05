#include "rooms.h"
#ifndef AVATAR_H
#define AVATAR_H

struct Avatar{
   char* name;
   struct Item* inventory;
   struct Room* location; 
};
struct Avatar* create_player(char* name);
void inventory(struct Avatar* name);
int take(char *itemName, struct Avatar *avatar);
int drop(char *itemName, struct Avatar *avatar);
void look(struct Avatar *name);
int move_player(struct Avatar *avatar, char *direction);
 
#endif
