#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./linked_list.h"

void destruct_null(void* nothing) {}

struct list_struct* new_linked_list() {
  List list = malloc(sizeof(struct list_struct));
  Node head = malloc(sizeof(struct node_struct));
  head->next = NULL;
  head->value = NULL;
  head->destructor = destruct_null;
  list->head = head;
  return list;
}

void free_node(Node node) {
  printf("Before freeing value node\n");
  node->destructor(node);
  printf("Done freeing node\n");
}

void free_linked_list(struct list_struct* list) {
  int done = 0;
  struct node_struct* item = NULL;
  while (!done) {
    item = remove_head_from_list(list);
    if (!item->next) {
      done = 1;
    }
    free_node(item);
  }
  free(list);
}

void add_to_list(
  List list,
  void* new_head_value,
  free_fn destructor
) {
  Node new_head = malloc(sizeof(struct node_struct));
  new_head->value = new_head_value;
  new_head->next = list->head;
  new_head->destructor = destructor;
  list->head = new_head;
}

void* remove_head_from_list(List list) {
  if (!list->head) {
    return list;
  }
  struct node_struct* head = list->head;
  list->head = list->head->next;
  return head;
}

void print_linked_list(struct list_struct* list) {
  printf("List:\n");
  printf("  Head: %s\n", (char*)list->head->value);
}

void each_of_list(List list, each_of_fn cb) {
  Node current_node = list->head;
  int i = 0;
  while (current_node->next) {
    printf("Loop: current index: %d\n", i);
    cb(current_node->value, i);
    current_node = current_node->next;
    i++;
  }
}
