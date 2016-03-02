#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./linked_list.h"

struct list* new_linked_list() {
  struct list* list = malloc(sizeof(struct list));
  struct node* head = malloc(sizeof(struct node));
  head->next = NULL;
  head->value = NULL;
  list->head = head;
  return list;
}

void free_node(struct node* node) {
  printf("FREEING NODE with val: %s\n", node->value);
  free(node->value);
  printf("After freeing value node\n");
  free(node);
  printf("Done freeing node\n");
}

void free_linked_list(struct list* list) {
  int done = 0;
  struct node* item = NULL;
  while (!done) {
    item = remove_head_from_list(list);
    if (!item->next) {
      done = 1;
    }
    free_node(item);
  }
  free(list);
}

void add_to_list(struct list* list, char* new_head_value) {
  struct node* new_head = malloc(sizeof(struct node));
  new_head->value = malloc(sizeof(char) * (strlen(new_head_value) + 1));
  strcpy(new_head->value, new_head_value);
  new_head->next = list->head;
  list->head = new_head;
}

void* remove_head_from_list(struct list* list) {
  if (!list->head) {
    return list;
  }
  struct node* head = list->head;
  list->head = list->head->next;
  return head;
}

void print_linked_list(struct list* list) {
  printf("List:\n");
  printf("  Head: %s\n", (char*)list->head->value);
}
