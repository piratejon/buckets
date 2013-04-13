#ifndef _JS_AVL_H

#include <sys/types.h>

typedef struct _tag_btnode {
  void * bucket;
  struct _tag_btnode * left, * right;
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

#endif // _JS_AVL_H

