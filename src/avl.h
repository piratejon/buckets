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

typedef struct _tag_int_bucket {
  int p;
} IntBucket;

AVLTree * init_avl_tree ( size_t bucket_size, int(*cmp)(void*,void*) );
void destroy_avl_tree ( AVLTree *);
void avl_tree_insert ( AVLTree *, void * );
int bucket_int_compare ( IntBucket *, IntBucket * );
BTNode * init_btnode(size_t);
void destroy_btnode(BTNode *);
BTNode * bst_insert ( AVLTree * t, void * p );
_Bool avl_verify_consistency(BTNode * s);

#endif // _JS_AVL_H

