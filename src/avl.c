
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

void bst_update_height_no_bubble(BTNode * sub_root) {
  sub_root->height = avl_tree_new_height(sub_root);
  sub_root->balance_factor = avl_tree_new_balance_factor(sub_root);
}

void bst_update_heights_bubble_upward(BTNode * sub_root) {
  // O(lg n) height and balance factor correction
  BTNode * parent = sub_root;
  while (parent) {
    bst_update_height_no_bubble(parent);
    parent = parent->parent;
  }
}

BTNode * bst_insert ( AVLTree * t, void * p ) {
  // this is a normal BST insert
  _Bool height_changed = false;
  BTNode * sub_root = t->root;
  if (!sub_root) {
    sub_root = t->root = init_btnode(t->bucket_size);
    memcpy(t->root->bucket, p, t->bucket_size);
  } else {
    while (1) { // O(lg n) insertion
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
    bst_update_heights_bubble_upward(sub_root); // O(lg n)
  }

  return sub_root;
}

void rotate_left(BTNode * s) {
  void * t;
  BTNode * a, * b, * c, * l;

  l = s->parent;

  a = l->left;
  b = s->left;
  c = s->right;

  l->left = s; s->parent = l;
  l->right = c; if (c) c->parent = l;
  s->right = b; if (b) b->parent = s;
  s->left = a; if (a) a->parent = s;

  t = s->bucket;
  s->bucket = l->bucket;
  l->bucket = t;
}

void rotate_right(BTNode * s) {
  void * t;
  BTNode * c, * d, * l;

  l = s->parent;

  c = s->right;
  d = l->right;

  l->left = s->left; if (l->left) l->left->parent = l;
  s->left = s->right;
  s->right = l->right; if (l->right) l->right->parent = l;
  l->right = s;

  t = s->bucket;
  s->bucket = l->bucket;
  l->bucket = t;
}

void avl_tree_insert ( AVLTree * t, void * p ) {
  BTNode * new_node, * parent;

  new_node = bst_insert(t, p);
  parent = new_node->parent;

  while (parent) { // O(lg n) AVL invariant inspection
    if (parent->balance_factor > 1) { // Left-left or Left-right
      if (parent->left->balance_factor < 0) { // Left-right
        rotate_left(parent->left->right);
        bst_update_heights_bubble_upward(parent->left->left);
      }
      rotate_right(parent->left); // happens in both LL and Lr cases
      bst_update_heights_bubble_upward(parent->right);
    } else if (parent->balance_factor < -1) { // Right-left or Right-right
      if (parent->right->balance_factor > 0) { // Right-left
        rotate_right(parent->right->left);
        bst_update_heights_bubble_upward(parent->right->right);
      }
      rotate_left(parent->right);
      bst_update_heights_bubble_upward(parent->left);
    }
    parent = parent->parent;
  }
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

_Bool avl_verify_consistency(BTNode * s) {
  if (s->parent) {
    if (s->parent->right != s && s->parent->left != s) {
      return false;
    }
  }

  if (s->left) {
    if (s->left->parent != s) {
      fprintf(stderr, "node %d has wrong parent\n", ((IntBucket*)s->bucket)->p);
      return false;
    }
    if (!avl_verify_consistency(s->left)) {
      fprintf(stderr, "left child inconsistent\n");
      return false;
    }
  }

  if (s->right) {
    if (s->right->parent != s) {
      fprintf(stderr, "node %d has wrong parent\n", ((IntBucket*)s->bucket)->p);
      return false;
    }
    if (!avl_verify_consistency(s->right)) {
      fprintf(stderr, "right child inconsistent\n");
      return false;
    }
  }

  return true;
}

