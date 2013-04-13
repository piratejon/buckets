
#include "avl.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void init_avl_tree ( void )
{
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( init_avl_tree );
}

