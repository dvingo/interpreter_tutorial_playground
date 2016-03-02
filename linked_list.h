#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
  struct node* next;
  void* value;
};

struct list {
  struct node* head;
};

struct list* new_linked_list();
void free_linked_list(struct list*);
void add_to_list(struct list*, char*);
void* remove_head_from_list(struct list*);
void print_linked_list(struct list*);
void free_node(struct node*);

#endif
