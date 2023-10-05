#include <stdio.h>
#ifndef ITEMS_H
#define ITEMS_H
struct Item{
   char* name;
   struct Item* next;
   struct Item* prev;
};
struct Item* create_item(char* item);
void add_item(struct Item* item, struct Item** head);
struct Item* drop_item(struct Item* item, struct Item** head);
void print_list(struct Item* head);

#endif
