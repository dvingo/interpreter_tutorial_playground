#include "./dbl_linked_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void destruct_string(void* str) {
  free(str);
}

void print_item(void* item, int i) {
  printf("Got item: %p at index %d\n", item, i);
  printf("Val: %s\n", item);
}

int main() {
  printf("file is: %s\n", __FILE__);

  DblList list = new_linked_list();
  assert(list->head->destructor);
  assert(list->head->next == NULL);
  assert(list->head->prev == NULL);
  assert(list->tail->destructor);
  assert(list->tail->next == NULL);
  assert(list->tail->prev == NULL);
  assert(list);

  print_linked_list(list);
  printf("\n");

  char* my_string = "my string";
  add_to_list(list, strdup(my_string), destruct_string);
  assert(list->head);
  assert(list->tail);
  assert(list->head->value != list->tail->value);
  assert(list->head->next->prev->value == list->head->value);
  print_linked_list(list);
  printf("\n");

  DblNode old_head = remove_head_from_list(list);
  printf("before strcmp\n");
  assert(strcmp(old_head->value, "my string") == 0);
  assert(list->head->next == NULL);
  free_node(old_head);

  char* my_string2 = "my string TWO";
  add_to_list(list, strdup(my_string2), destruct_string);
  print_linked_list(list);
  add_to_list(list, "my_string2)", destruct_null);
  add_to_list(list, strdup("strdup(my_string3)"), destruct_string);
  add_to_list(list, strdup("LAST GUY HERE"), destruct_string);
  printf("Before each of list\n");
  each_of_list(list, print_item);
  printf("After each of list \n\n");

  each_of_list_reverse(list, print_item);
  printf("After each of list reverse\n\n");

  printf("\n");
  printf("before free list\n");
  free_linked_list(list);
  printf("after free list\n");
  return 0;
}
