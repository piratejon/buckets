
#include <stdbool.h>
#include <stdlib.h>

#include "qt.h"

int point_compare_x ( Point * a, Point * b ) {
  if ( a->x < b->x ) return -1;
  else if ( a->x > b->x ) return 1;
  else return 0;
}

int point_compare_y ( Point * a, Point * b ) {
  if ( a->y < b->y ) return -1;
  else if ( a->y > b->y ) return 1;
  else return 0;
}

QuadTree * init_quadtree(size_t t) {
  QuadTree * qt = malloc(sizeof(QuadTree));
  qt->root = malloc(sizeof(QTNode));
  qt->root->nw = qt->root->ne = qt->root->sw = qt->root->se = NULL;
  qt->root->children = init_avl_tree(sizeof(Point), point_compare_x);
  qt->root->balance = X;
  return qt;
}

void destroy_quadtree_nodes(QTNode * qt) {
  if (qt->nw) destroy_quadtree_nodes(qt->nw);
  if (qt->ne) destroy_quadtree_nodes(qt->ne);
  if (qt->sw) destroy_quadtree_nodes(qt->sw);
  if (qt->se) destroy_quadtree_nodes(qt->se);
  if (qt->children) destroy_avl_tree(qt->children);
  free(qt);
}

void destroy_quadtree ( QuadTree * qt ) {
  destroy_quadtree_nodes(qt->root);
  free(qt);
}

