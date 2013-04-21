
#include "qt.h"

QuadTree * init_quadtree() {
  return malloc(1);;
}

void destroy_quadtree ( QuadTree * qt ) {
  free(qt);
}

