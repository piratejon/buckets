
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
  return (sub_root->left ? sub_root->left->height : 0) - (sub_root->right ? sub_root->right->height : 0);
}

int avl_tree_new_height ( BTNode * sub_root ) {
  return MAX2(sub_root->right ? sub_root->right->height : 0, sub_root->left ? sub_root->left->height : 0) + 1;
}

void rotate_to_the_left(BTNode * sub_root) {
}

_Bool rotate_to_the_right(BTNode * sub_root) {
  /**
    returns true if the height changed, false if not
    **/
  void * old_subroot_bucket = sub_root->bucket;
  BTNode * left = sub_root->left;
  sub_root->bucket = left->bucket;
}

_Bool avl_tree_correct_left_imbalance ( AVLTree * t, BTNode * sub_root ) {
  // this is a left imbalance. is it left-left or left-right?
  if (sub_root->balance_factor > 0) { // left-right
    //  rotate sub_root->left->right to the left, then rotate
  } else {
    // left-left
  }
  // rotate sub_root->left to the right
  return rotate_to_the_right(sub_root);
}

BTNode * bst_insert ( AVLTree * t, void * p ) {
  // this is a normal BST insert
  _Bool height_changed = false;
  BTNode * sub_root = t->root;
  if (!sub_root) {
    t->root = init_btnode(t->bucket_size);
    memcpy(t->root->bucket, p, t->bucket_size);
  } else {
    while (1) {
      int cmp = (*(t->cmp))(sub_root->bucket, p);
      sub_root->count += 1;
      if (cmp < 0) {
        if (sub_root->right) sub_root = sub_root->right;
        else {
          sub_root->right = init_btnode(t->bucket_size);
          sub_root->right->parent = sub_root;
          memcpy(sub_root->right->bucket, p, t->bucket_size);
          if (NULL == sub_root->left) height_changed = true;
          sub_root = sub_root->right;
          break;
        }
      } else if (cmp > 0) {
        if (sub_root->left) sub_root = sub_root->left;
        else {
          sub_root->left = init_btnode(t->bucket_size);
          sub_root->left->parent = sub_root;
          memcpy(sub_root->left->bucket, p, t->bucket_size);
          if (NULL == sub_root->right) height_changed = true;
          sub_root = sub_root->left;
          break;
        }
      } else {
        sub_root->multiplicity += 1;
        break;
      }
    }
  }

  if (height_changed) {
    BTNode * parent = sub_root->parent;
    while (parent) {
      parent->height = avl_tree_new_height(parent);
      parent->balance_factor = avl_tree_new_balance_factor(parent);
      parent = parent->parent;
    }
  }

  return sub_root;
}

void avl_tree_insert ( AVLTree * t, void * p ) {
  if ( !t->root ) {
    t->root = init_btnode(t->bucket_size);
    memcpy(t->root->bucket, p, t->bucket_size);
  } else {
    // avl_tree_insert_at_node(t, t->root, p);
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
  out->parent = NULL;
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

