
#include <sys/types.h>
#include <stdlib.h>

#include "avl.h"

AVLTree * init_avl_tree ( size_t bucket_size, int (*cmp)(void *, void *) ) {
  AVLTree * out = malloc(sizeof(AVLTree));
  out->bucket_size = bucket_size;
  out->cmp = cmp;
  return out;
}

void destroy_avl_tree ( AVLTree * t ) {
  free(t);
}

void avl_tree_insert ( AVLTree * t, void * p ) {
  return;
}

int bucket_int_compare ( IntBucket * a, IntBucket * b)
{
  if ( a->p > b->p ) return 1;
  else if ( a->p < b->p ) return -1;
  else return 0;
}

