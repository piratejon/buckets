
#include <stdbool.h>

#include "tests.h"
#include "avl.h"
#include "qt.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void test_initialize_quadtree ( void )
{
  QuadTree * qt = init_quadtree();

  ASSERT ( qt, "NULL quadtree");

  destroy_quadtree(qt);
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( test_initialize_quadtree );
}

