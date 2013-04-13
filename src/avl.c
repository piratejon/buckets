
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "avl.h"

AVLTree * init_avl_tree ( size_t bucket_size, int (*cmp)(void *, void *) ) {
  AVLTree * out = malloc(sizeof(AVLTree));
  out->bucket_size = bucket_size;
  out->cmp = cmp;
  out->root = NULL;
  return out;
}

void destroy_avl_tree ( AVLTree * t ) {
  if (t->root) destroy_btnode(t->root);
  free(t);
}

void avl_tree_insert_at_node ( AVLTree * t, BTNode * b, void * p ) {
  int cmp = (*(t->cmp))(p, b->bucket);
  if (cmp > 0) {
    if (b->right) {
      avl_tree_insert_at_node(t, b->right, p);
    } else {
      b->right = init_btnode(t->bucket_size);
      memcpy(b->right->bucket, p, t->bucket_size);
    }
  } else if (cmp < 0) {
    if (b->left) {
      avl_tree_insert_at_node(t, b->left, p);
    } else {
      b->left = init_btnode(t->bucket_size);
      memcpy(b->left->bucket, p, t->bucket_size);
    }
  } else {
    // lol
  }
}

void avl_tree_insert ( AVLTree * t, void * p ) {
  if ( !t->root ) {
    t->root = init_btnode(t->bucket_size);
    memcpy(t->root->bucket, p, t->bucket_size);
  } else {
    avl_tree_insert_at_node(t, t->root, p);
  }
  return;
}

int bucket_int_compare ( IntBucket * a, IntBucket * b)
{
  if ( a->p > b->p ) return 1;
  else if ( a->p < b->p ) return -1;
  else return 0;
}

BTNode * init_btnode(size_t s) {
  BTNode * out = malloc(sizeof(BTNode));
  out->bucket = malloc(s);
  out->left = NULL;
  out->right = NULL;
  return out;
}

void destroy_btnode(BTNode * b) {
  free(b->bucket);
  if (b->left) destroy_btnode(b->left);
  if (b->right) destroy_btnode(b->right);
  free(b);
}

