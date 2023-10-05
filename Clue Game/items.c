#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "items.h"
struct Item* create_item(char* name){
   struct Item *newItem = (struct Item*)malloc(sizeof(struct Item)); //dynamic alloc
   newItem->name = name;
   newItem->next = NULL;
   newItem->prev = NULL;
   return newItem;
}

//adds an item to any linked list
void add_item(struct Item* item, struct Item** head){
   struct Item* temp = *head;
   *head = item;
   (*head)->prev = NULL;
  (* head)->next = NULL;
    if(temp!=NULL){
      (*head)->next = temp;
      (*head)->prev = NULL;
      temp->prev = *head;
   }
}
//removes an item from any linked list
struct Item* drop_item(struct Item* item, struct Item** head){
   struct Item* traverse = *head;
   while(traverse!=NULL){
      if(strcmp(traverse->name, item->name)==0){
         break;
      }
      traverse = traverse->next;        
   }
   if(traverse!=NULL){
      if(traverse->prev == NULL){
         *head = (*head)->next;
         if(traverse->next != NULL){
             (*head)->prev = NULL;
             traverse->next = NULL;
         }
      }
      else{
          if(traverse->next == NULL){
             (traverse->prev)->next = NULL;
              traverse->prev = NULL;
          }
          else{
             (traverse->prev)->next = traverse->next;
             (traverse->next)->prev = traverse->prev;
              traverse->prev = NULL;
              traverse->next = NULL;
          }
      }
   }
  return traverse;
}
/*
void print_list(struct Item* head){
   struct Item* traverse = head;
   while(traverse != NULL){
      printf("%s", traverse->name);
      traverse = traverse->next;
   }
   printf("\n");
}
*/
