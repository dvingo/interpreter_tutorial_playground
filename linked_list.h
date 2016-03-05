#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef void (*free_fn)(void*);
typedef void (*each_of_fn)(void*, int i);
void destruct_null(void*);

typedef struct node_struct* Node;
struct node_struct {
  Node next;
  void* value;
  free_fn destructor;
};

typedef struct list_struct* List;
struct list_struct {
  Node head;
};

struct list_struct* new_linked_list();
void free_linked_list(struct list_struct*);
void add_to_list(struct list_struct*, void*, free_fn);
void* remove_head_from_list(struct list_struct*);
void print_linked_list(struct list_struct*);
void free_node(struct node_struct*);
void each_of_list(List, each_of_fn);

#endif
