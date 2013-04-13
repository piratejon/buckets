#ifndef _JS_AVL_H

#include <sys/types.h>

typedef struct _tag_avltree {
  size_t bucket_size;
} AVLTree;

AVLTree * init_avl_tree ( size_t bucket_size );

#endif // _JS_AVL_H

