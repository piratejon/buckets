#ifndef _JS_QT_H
#define _JS_QT_H

#include <sys/types.h>

#include "avl.h"

// #define MAX2(x,y) (((x)>(y))?(x):(y))

typedef struct _tag_qtnode {
  void * payload;
  int x, y;

  AVLTree * children; // for determining median child quickly
  struct _tag_qtnode * nw, * sw, * ne, * se;
} QTNode;

typedef struct _tag_qt {
  QTNode * root;
} QuadTree;

QuadTree * init_quadtree();

#endif // _JS_QT_H

