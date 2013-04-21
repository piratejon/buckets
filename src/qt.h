#ifndef _JS_QT_H
#define _JS_QT_H

#include <sys/types.h>

#include "avl.h"

// #define MAX2(x,y) (((x)>(y))?(x):(y))

typedef enum _tag_dim {
  X, Y
} Dimension;

typedef struct _tag_point {
  int x, y;
} Point;

typedef struct _tag_qtnode {
  void * payload;
  Point p;

  AVLTree * children; // for determining median child quickly
  struct _tag_qtnode * nw, * sw, * ne, * se;
  Dimension balance;
} QTNode;

typedef struct _tag_qt {
  QTNode * root;
} QuadTree;

QuadTree * init_quadtree(size_t);
void destroy_quadtree ( QuadTree * qt );

#endif // _JS_QT_H

