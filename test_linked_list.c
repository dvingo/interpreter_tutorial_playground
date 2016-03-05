#include "./linked_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void destruct_string(void* str) {
  free(str);
}

void print_item(void* item, int i) {
  printf("Got item: %p at index %d\n", item, i);
  printf("Val: %s\n", ((Node)item)->value);
}

int main() {
  printf("file is: %s\n", __FILE__);

  List list = new_linked_list();
  assert(list->head->destructor != NULL);
  assert(list->head->destructor);
  assert(list);

  print_linked_list(list);
  printf("\n");

  char* my_string = "my string";
  add_to_list(list, strdup(my_string), destruct_string);
  assert(list->head);
  print_linked_list(list);
  printf("\n");

  Node old_head = remove_head_from_list(list);
  printf("before strcmp\n");
  assert(strcmp(old_head->value, "my string") == 0);
  assert(list->head->next == NULL);
  free_node(old_head);

  char* my_string2 = "my string TWO";
  add_to_list(list, strdup(my_string2), destruct_string);
  print_linked_list(list);

  // char* my_string2 = "my string TWO";
  add_to_list(list, "strdup(my_string2)", destruct_string);
  add_to_list(list, "strdup(my_string3)", destruct_string);
  add_to_list(list, "LAST GUY HERE", destruct_string);

  each_of_list(list, print_item);

  printf("\n");
  printf("before free list\n");
  free_linked_list(list);
  printf("after free list\n");
  return 0;
}
