#include "items.h"
#ifndef ROOMS_H
#define ROOMS_H
struct Room{
   char* name;
   struct Room* north;
   struct Room* south;
   struct Room* east;
   struct Room* west;
   struct Item* itemList;
   char* characters[5];
};
struct Room* create_room(char* name);
struct Clue* create_answer(char** characters, struct Item** items, struct Room** rooms);
void room_dir(struct Room* curRoom);
void room_chars(struct Room* curRoom);
void room_items(struct Room* curRoom);
void create_gameboard(struct Room** rooms);
void item_insert(struct Item **items, struct Room **rooms);
void char_insert(char **characterNames, struct Room **rooms);
#endif
