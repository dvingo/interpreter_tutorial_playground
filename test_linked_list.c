#include "./linked_list.h"
#include <stdio.h>

int main() {
  
  struct list* list = new_linked_list();
  print_linked_list(list);
  printf("\n");

  char* my_string = "my string";
  add_to_list(list, my_string);
  print_linked_list(list);
  printf("\n");

  struct node* old_head = remove_head_from_list(list);
  free_node(old_head);

  char* my_string2 = "my string TWO";
  add_to_list(list, my_string2);
  print_linked_list(list);

  printf("\n");
  free_linked_list(list);
  return 0;
}
