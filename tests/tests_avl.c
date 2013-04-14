
#include "avl.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void avl_bucket_int_compare ( void )
{
  IntBucket a, b;
  a.p = 9;
  b.p = -99;
  ASSERT ( bucket_int_compare ( &a, &b ) > 0, "9 failed to be greater than -99" );
  b.p = 99;
  ASSERT ( a.p == 9, "9 fails to be equal to 9" );
  ASSERT ( b.p == 99, "99 fails to be equal to its own self" );
  ASSERT ( bucket_int_compare ( &a, &b ) < 0, "9 failed to be less than 99" );
  a.p = 99;
  ASSERT ( bucket_int_compare ( &a, &b ) == 0, "99 failed to be equale to 99" );
}

void avl_tree_init_destroy ( void )
{
  AVLTree * t = init_avl_tree(sizeof(int*), &bucket_int_compare);
  ASSERT ( t, "init_avl_tree returned null" );
  destroy_avl_tree ( t );
}

void avl_tree_insert_elements ( void )
{
  IntBucket *a,*b,*c,*d,*e,*f,*g,*h;
  a = malloc(sizeof(IntBucket));
  b = malloc(sizeof(IntBucket));
  c = malloc(sizeof(IntBucket));

  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);

  a->p = 99;
  b->p = 8;
  c->p = 7;

  avl_tree_insert ( t, a );
  ASSERT (t->root->count == 1, "Wrong count of children.");
  ASSERT (t->root->height == 1, "Root with no children has wrong height.");
  ASSERT (t->root->balance_factor == 0, "Root with no children has wrong balance factor.");
  avl_tree_insert ( t, b );
  ASSERT (t->root->count == 2, "Wrong count of children in root after inserting one child.");
  ASSERT (t->root->height == 2, "Wrong height for root with one child.");
  ASSERT (t->root->balance_factor == -1, "Root with one child has wrong balance factor.");
  ASSERT (t->root->left->count == 1, "Child has wrong count.");
  ASSERT (t->root->left->height == 1, "Child has wrong height.");
  ASSERT (t->root->left->balance_factor == 0, "Root with no children has wrong balance factor.");

  ASSERT ( ((IntBucket*)(t->root->bucket))->p == 99, "Wrong value for root" );
  ASSERT ( ((IntBucket*)(t->root->left->bucket))->p == 8, "Wrong value for left child" );

  avl_tree_insert(t,c); // ROOT->LEFT->LEFT
  ASSERT(t->root->count==3, "Wrong count of children at root after 2nd insert");
  ASSERT(t->root->height==3, "Wrong height after 2nd insert");
  ASSERT(t->root->balance_factor==-2, "Wrong balance factor after 2nd insert");
  ASSERT(t->root->left->count==2, "Wrong child count after 2nd insert");
  ASSERT(t->root->left->height==2, "Wrong child height after 2nd insert");
  ASSERT(t->root->left->balance_factor==-1, "Wrong child balance factor after 2nd insert");

  destroy_avl_tree(t);

  free(c);
  free(b);
  free(a);
}

void btnode_initialize_destroy ( void )
{
  BTNode * b = init_btnode(sizeof(IntBucket));

  ASSERT ( b->left == NULL, "left is not null" );
  ASSERT ( b->right == NULL, "right is not null" );
  ASSERT ( b->bucket != NULL, "bucket is null!" );

  destroy_btnode(b);
}

void avl_tree_bst_helpers ( void )
{
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);

  IntBucket *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k;

  a = malloc(sizeof(IntBucket));
  b = malloc(sizeof(IntBucket));
  c = malloc(sizeof(IntBucket));
  d = malloc(sizeof(IntBucket));
  e = malloc(sizeof(IntBucket));
  f = malloc(sizeof(IntBucket));
  g = malloc(sizeof(IntBucket));
  h = malloc(sizeof(IntBucket));
  i = malloc(sizeof(IntBucket));
  j = malloc(sizeof(IntBucket));
  k = malloc(sizeof(IntBucket));

  a->p = 99;
  b->p = 8;
  c->p = 33;
  d->p = 17;
  e->p = 86;
  f->p = 87;
  g->p = 93;
  h->p = 17;
  i->p = 150;
  j->p = 155;
  k->p = 140;

  bst_insert(t,a);
  ASSERT(t->root->count == 1, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor == 0, "Wrong balance factor.");
  ASSERT(t->root->left == NULL, "Left not NULL");
  ASSERT(t->root->right == NULL, "Right not NULL");

  bst_insert(t,b);
  ASSERT(t->root->count == 2, "Wrong count.");
  ASSERT(t->root->height == 2, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor == 1, "Wrong balance factor.");
  ASSERT(t->root->right == NULL, "Right not NULL");
  ASSERT(t->root->left != NULL, "Left NULL");
  ASSERT(t->root->left->count == 1, "Wrong count.");
  ASSERT(t->root->left->height == 1, "Wrong height.");
  ASSERT(t->root->left->left == NULL, "Left not NULL.");
  ASSERT(t->root->left->right == NULL, "Right not NULL.");

  /*
  bst_insert(t,c);
  ASSERT(t->root->count == 3, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,d);
  ASSERT(t->root->count == 4, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,e);
  ASSERT(t->root->count == 5, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,f);
  ASSERT(t->root->count == 6, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,g);
  ASSERT(t->root->count == 7, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,h);
  ASSERT(t->root->count == 8, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,i);
  ASSERT(t->root->count == 9, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,j);
  ASSERT(t->root->count == 10, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");

  bst_insert(t,k);
  ASSERT(t->root->count == 11, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 0, "Wrong balance factor.");
  */

  free(k);
  free(j);
  free(i);
  free(h);
  free(g);
  free(f);
  free(e);
  free(d);
  free(c);
  free(b);
  free(a);

  destroy_avl_tree(t);
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( avl_bucket_int_compare );
  TEST ( btnode_initialize_destroy );
  TEST ( avl_tree_init_destroy );
  TEST ( avl_tree_bst_helpers );
  // TEST ( avl_tree_insert_elements );
}

