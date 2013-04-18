
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
  s->right = l->right; if (s->right) s->right->parent = s;
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
        if (!avl_verify_consistency(t->root)) {
          fprintf(stderr, "left-heavy rotate left: Oh Shit!\n");
        }
      }
      rotate_right(parent->left); // happens in both LL and Lr cases
      bst_update_heights_bubble_upward(parent->right);
      if (!avl_verify_consistency(t->root)) {
        fprintf(stderr, "left-heavy rotate right: Oh Shit!\n");
      }
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
      fprintf(stderr, "node %d's parent does not have it as a child\n", ((IntBucket*)s->bucket)->p);
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

void avl_tree_traverse ( AVLTree * t, _Bool(*f)(BTNode*) ) {
  BTNode * cur, * last;

  cur = t->root;
  if (cur) {
    last = t->root->parent;
    while (cur) {
      if ( last == cur->parent ) { // coming down
        last = cur;
        if (cur->left) { // go left if we can
          cur = cur->left;
        } else if (cur->right) { // go right if we can't
          if (!(*f)(cur)) break;
          cur = cur->right;
        } else { // as a last resort, go back up
          if (!(*f)(cur)) break;
          cur = cur->parent;
        }
      } else if ( last == cur->left ) { // coming up from the left
        last = cur;
        if (!(*f)(cur)) break; // print out
        if (cur->right) { // go right if we can
          cur = cur->right;
        } else { // go back up
          cur = cur->parent;
        }
      } else if ( last == cur->right ) { // coming up from the right, just go up
        last = cur;
        cur = cur->parent;
      }
    }
  }
}

BTNode * avl_tree_get_nth_item ( BTNode * t, int index ) {
  int left_count, right_count;
  while ( index <= t->count ) {
    left_count = t->left ? t->left->count : 0;
    right_count = t->right ? t->right->count : 0;

    // fprintf(stderr, "looking at %d for index %d: (%d,%d,%d): ", ((IntBucket*)t->bucket)->p, index, left_count, t->multiplicity, right_count);

    if ( index <= left_count ) {
      // fprintf(stderr, "going left\n");
      t = t->left;
      continue;
    }

    index -= left_count;
    
    if ( index <= t->multiplicity ) {
      // fprintf(stderr, "found it\n");
      return t;
    }

    index -= t->multiplicity;
    
    if ( index <= right_count ) {
      // fprintf(stderr, "going right\n");
      t = t->right;
      continue;
    }

    return NULL;
  }

  return t;
}

BTNode * avl_tree_get_median ( AVLTree * t ) {
  if ( t->root ) {
    if ( t->root->count > 0 ) {
      return avl_tree_get_nth_item ( t->root, t->root->count / 2 );
    } else {
      return NULL;
    }
  } else {
    return NULL;
  }
}

