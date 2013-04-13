#ifndef _JS_AVL_H

#include <sys/types.h>

typedef struct _tag_avltree {
  size_t bucket_size;
  int (*cmp)(void *, void *);
} AVLTree;

typedef struct _tag_int_bucket {
  int p;
} IntBucket;

AVLTree * init_avl_tree ( size_t bucket_size, int(*cmp)(void*,void*) );
void destroy_avl_tree ( AVLTree *);
void avl_tree_insert ( AVLTree *, void * );
int bucket_int_compare ( IntBucket *, IntBucket * );

#endif // _JS_AVL_H

