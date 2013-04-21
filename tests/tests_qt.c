
#include <stdlib.h>

#include "tests.h"
#include "avl.h"
#include "qt.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void test_initialize_quadtree ( void )
{
  QuadTree * qt = init_quadtree(sizeof(int));

  ASSERT ( qt, "NULL quadtree");

  destroy_quadtree(qt);
}

void test_insert_points ( void ) {
  QuadTree * qt = init_quadtree(sizeof(int));

  int i, x, y;

  srand(1234567);

  for ( i = 0; i < 5000; i += 1 ) {
    x = rand();
    y = rand();
    // qt_insert(x, y, i);
  }

  destroy_quadtree(qt);
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( test_initialize_quadtree );
  TEST ( test_insert_points );
}

