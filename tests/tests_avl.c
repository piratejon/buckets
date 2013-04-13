
#include "avl.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void avl_tree_init_destroy ( void )
{
  AVLTree * t = init_avl_tree(sizeof(int*));
  ASSERT ( t, "init_avl_tree returned null" );
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( avl_tree_init_destroy );
}

