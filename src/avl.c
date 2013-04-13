
#include <sys/types.h>

#include "avl.h"

AVLTree * init_avl_tree ( size_t bucket_size ) {
  AVLTree * out = malloc(sizeof(AVLTree));
  out->bucket_size = bucket_size;
  return out;
}
