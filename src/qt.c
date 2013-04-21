
#include <stdlib.h>

#include "qt.h"

QuadTree * init_quadtree() {
  QuadTree * qt = malloc(sizeof(QuadTree));
  qt->root = malloc(sizeof(QTNode));
  qt->root->nw = qt->root->ne = qt->root->sw = qt->root->se = NULL;
  qt->root->children = NULL;
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

