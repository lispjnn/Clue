#include "items.h"
#include "rooms.h"
#include "avatar.h"
#ifndef CLUE_H
#define CLUE_H

struct Clue{
  struct Item *weapon;
  struct Room *room;
  char *murderer;
};

struct Clue* create_answer(char** characters, struct Item** items, struct Room** rooms);
int clue(struct Clue *answer, struct Room **rooms, struct Avatar *avatar, char *character, char *item); 

#endif
