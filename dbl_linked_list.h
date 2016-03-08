#ifndef DBL_LINKED_LIST_H
#define DBL_LINKED_LIST_H

typedef void (*free_fn)(void*);
typedef void (*each_of_fn)(void*, int i);
void destruct_null(void*);

typedef struct dbl_node_struct* DblNode;
struct dbl_node_struct {
  DblNode next;
  DblNode prev;
  void* value;
  free_fn destructor;
};

typedef struct dbl_list_struct* DblList;
struct dbl_list_struct {
  DblNode head;
  DblNode tail;
};

struct dbl_list_struct* new_linked_list();
void free_linked_list(struct dbl_list_struct*);
void add_to_list(struct dbl_list_struct*, void*, free_fn);
void* remove_head_from_list(struct dbl_list_struct*);
void print_linked_list(struct dbl_list_struct*);
void free_node(struct dbl_node_struct*);
void each_of_list(DblList, each_of_fn);
void each_of_list_reverse(DblList, each_of_fn);

#endif
