
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

QTNode * init_qtnode(Point * pt, void * payload) {
  QTNode * n;
  n = malloc(sizeof(QTNode));
  memcpy(&(n->p), pt, sizeof*pt);
  n->payload = payload;
  n->nw = n->ne = n->sw = n->se = NULL;
  n->children = init_avl_tree(sizeof(Point), point_compare_x);
  n->balance = X;
  return n;
}

QuadTree * init_quadtree(size_t t) {
  QuadTree * qt = malloc(sizeof(QuadTree));
  qt->root = NULL;
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
  if (qt->root) destroy_quadtree_nodes(qt->root);
  free(qt);
}

Dimension next_dimension ( Dimension d ) {
  switch ( d ) {
    case X: return Y;
    case Y: // return X;
    default: return X;
  }
}

QTNode * qt_node_insert ( QTNode * qt, Point * pt, void * payload ) {
  while ( 1 ) {
    if ( pt->x > qt->p.x ) {
      if ( pt->y > qt->p.y ) {
        if ( qt->nw ) {
          qt = qt->nw;
        } else {
          qt->nw = init_qtnode(pt, payload);
          return qt->nw;
        }
      } else {
        if ( qt->sw ) {
          qt = qt->sw;
        } else {
          qt->sw = init_qtnode(pt, payload);
          return qt->sw;
        }
      }
    } else {
      if ( pt->y > qt->p.y ) {
        if ( qt->ne ) {
          qt = qt->ne;
        } else {
          qt->ne = init_qtnode(pt, payload);
          return qt->ne;
        }
      } else {
        // silently drop duplicates
        if ( pt->x == qt->p.x ) return NULL;
        if ( qt->se ) {
          qt = qt->se;
        } else {
          qt->se = init_qtnode(pt, payload);
          return qt->se;
        }
      }
    }
  }
}

QTNode * qt_insert ( QuadTree * qt, Point * pt, void * payload ) {
  if ( qt->root ) {
    return qt_node_insert ( qt->root, pt, payload );
  } else {
    qt->root = init_qtnode(pt, payload);
    return qt->root;
  }
}

void qt_node_traverse ( QTNode * qt, _Bool(*f)(QTNode*) ) {
  (*f)(qt);
  if ( qt->nw ) qt_node_traverse(qt->nw, f);
  if ( qt->ne ) qt_node_traverse(qt->ne, f);
  if ( qt->sw ) qt_node_traverse(qt->sw, f);
  if ( qt->se ) qt_node_traverse(qt->se, f);
}

void qt_traverse ( QuadTree * qt, _Bool(*f)(QTNode*) ) {
  if ( qt->root ) qt_node_traverse(qt->root, f);
}

