#ifndef _JS_AVL_H

#include <sys/types.h>

#define MAX2(x,y) (((x)>(y))?(x):(y))

typedef struct _tag_btnode {
  void * bucket;
  struct _tag_btnode * left, * right, * parent;
  int count; // self->multiplicity + left->count + right->count
  int balance_factor; // left->height - right->height
  int multiplicity; // how many of this element in the multiset
  int height; // height of this (sub)tree. in a single-element tree, the root has height 1
} BTNode;

typedef struct _tag_avltree {
  size_t bucket_size;
  int (*cmp)(void *, void *);
  BTNode * root;
} AVLTree;

AVLTree * init_avl_tree ( size_t bucket_size, int(*cmp)(void*,void*) );
void destroy_avl_tree ( AVLTree *);
void avl_tree_insert ( AVLTree *, void * );
BTNode * init_btnode(size_t);
void destroy_btnode(BTNode *);
BTNode * bst_insert ( AVLTree * t, void * p );
_Bool avl_verify_consistency(AVLTree * t, BTNode * s);
void avl_tree_traverse ( AVLTree * t, _Bool(*f)(BTNode*) );
BTNode * avl_tree_get_median ( AVLTree * t );
BTNode * avl_tree_get_nth_item ( BTNode * t, int index );
void avl_delete_node ( AVLTree * t, BTNode * d );
BTNode * avl_find_exact ( AVLTree * t, void * );

#endif // _JS_AVL_H

