#include "./dbl_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void destruct_null(void* nothing) {}

struct dbl_list_struct* new_linked_list() {
  DblList list = malloc(sizeof(struct dbl_list_struct));
  DblNode head = malloc(sizeof(struct dbl_node_struct));
  head->next = NULL;
  head->prev = NULL;
  head->value = NULL;
  head->destructor = destruct_null;
  list->head = head;

  DblNode tail = malloc(sizeof(struct dbl_node_struct));
  tail->next = NULL;
  tail->prev = NULL;
  tail->value = NULL;
  tail->destructor = destruct_null;
  list->tail = tail;

  return list;
}

void free_node(DblNode node) {
  printf("Before freeing value node\n");
  node->destructor(node->value);
  free(node);
  printf("Done freeing node\n");
}

void free_linked_list(DblList list) {
  int done = 0;
  DblNode item = NULL;
  while (!done) {
    printf("before remove_head_from_list\n");
    item = remove_head_from_list(list);
    if (!item->next) {
      done = 1;
    }
    free_node(item);
  }
  free(list);
}

void add_to_list(
  DblList list,
  void* new_head_value,
  free_fn destructor
) {
  DblNode new_head = malloc(sizeof(struct dbl_node_struct));
  new_head->value = new_head_value;
  new_head->next = list->head;
  new_head->prev = NULL;
  new_head->destructor = destructor;
  list->head->prev = new_head;
  list->head = new_head;
  if (list->tail->prev == NULL) {
    list->tail->prev = list->head;
  }
}

void* remove_head_from_list(DblList list) {
  if (!list->head) {
    return list;
  }
  DblNode head = list->head;
  list->head = list->head->next;
  if (list->head) {
    list->head->prev = NULL;
  }

  if (list->tail->prev == head) {
    list->tail->prev = NULL;
  }
  return head;
}

void print_linked_list(struct dbl_list_struct* list) {
  printf("List:\n");
  printf("  Head: %s\n", (char*)list->head->value);
}

void each_of_list(DblList list, each_of_fn cb) {
  DblNode current_node = list->head;
  int i = 0;
  while (current_node->next) {
    printf("Loop: current index: %d\n", i);
    cb(current_node->value, i);
    current_node = current_node->next;
    i++;
  }
}

void each_of_list_reverse(DblList list, each_of_fn cb) {
  DblNode current_node = list->tail;
  int i = 0;
  if (list->tail->prev) {
    current_node = list->tail->prev;
  }
  while (current_node) {
    printf("Loop: current index: %d\n", i);
    cb(current_node->value, i);
    current_node = current_node->prev;
    i++;
  }
}
