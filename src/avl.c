
#include <sys/types.h>
#include <stdbool.h>
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

int avl_tree_new_balance_factor ( BTNode * sub_root ) {
  return (sub_root->right ? sub_root->right->height : 0) - (sub_root->left ? sub_root->left->height : 0);
}

_Bool avl_tree_insert_at_node ( AVLTree * t, BTNode * sub_root, void * p ) {
  /**
    returns true if the height changed, false if not
    **/
  int cmp = (*(t->cmp))(sub_root->bucket, p);
  if (cmp < 0) {
    return false;
  } else if (cmp > 0) {
    sub_root->count ++;
    if (!sub_root->left) {
      sub_root->left = init_btnode(t->bucket_size);
      memcpy(sub_root->left->bucket, p, t->bucket_size);
      if (sub_root->right) {
        sub_root->balance_factor = sub_root->right->height - 1;
        return false;
      } else {
        sub_root->balance_factor = -1;
        sub_root->height ++;
        return true;
      }
    } else {
      if (avl_tree_insert_at_node(t, sub_root->left, p)) {
        sub_root->height = sub_root->left->height + 1;
        sub_root->balance_factor = avl_tree_new_balance_factor(sub_root);
        return true;
      } else {
        return false;
      }
    }
  } else {
    sub_root->multiplicity ++;
    return false;
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

int bucket_int_compare ( IntBucket * a, IntBucket * b) {
  if ( a->p > b->p ) return 1;
  else if ( a->p < b->p ) return -1;
  else return 0;
}

BTNode * init_btnode(size_t s) {
  BTNode * out = malloc(sizeof(BTNode));
  out->bucket = malloc(s);
  out->left = NULL;
  out->right = NULL;
  out->count = 1;
  out->height = 1;
  out->multiplicity = 1;
  out->balance_factor = 0;
  return out;
}

void destroy_btnode(BTNode * b) {
  free(b->bucket);
  if (b->left) destroy_btnode(b->left);
  if (b->right) destroy_btnode(b->right);
  free(b);
}

