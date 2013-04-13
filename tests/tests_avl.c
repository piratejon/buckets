
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

  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);

  a->p = 99;
  b->p = 8;

  avl_tree_insert ( t, a );
  avl_tree_insert ( t, b );

  ASSERT ( t->root->bucket->p == 99, "Wrong value for root" );
  ASSERT ( t->root->left->bucket->p == 8, "Wrong value for left child" );

  destroy_avl_tree(t);

  free(b);
  free(a);
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( avl_bucket_int_compare );
  TEST ( avl_tree_init_destroy );
  TEST ( avl_tree_insert_elements );
}

