
#include <stdbool.h>

#include "avl.h"
#include "tests.h"

void sanity_check_zero ( void )
{
  ASSERT ( 0 == 0, "Zero failed to be equal to zero." );
}

void avl_bucket_int_compare ( void )
{
  IntBucket a, b;
  a.p = 9;
  b.p = -99;
  ASSERT ( bucket_int_compare ( &a, &b ) > 0, "9 failed to be greater than -99" );
  b.p = 99;
  ASSERT ( a.p == 9, "9 fails to be equal to 9" );
  ASSERT ( b.p == 99, "99 fails to be equal to its own self" );
  ASSERT ( bucket_int_compare ( &a, &b ) < 0, "9 failed to be less than 99" );
  a.p = 99;
  ASSERT ( bucket_int_compare ( &a, &b ) == 0, "99 failed to be equale to 99" );
}

void avl_tree_init_destroy ( void )
{
  AVLTree * t = init_avl_tree(sizeof(int*), &bucket_int_compare);
  ASSERT ( t, "init_avl_tree returned null" );
  destroy_avl_tree ( t );
}

void avl_tree_insert_elements ( void )
{
  IntBucket *a,*b,*c,*d,*e,*f,*g,*h;
  a = malloc(sizeof(IntBucket));
  b = malloc(sizeof(IntBucket));
  c = malloc(sizeof(IntBucket));
  d = malloc(sizeof(IntBucket));
  e = malloc(sizeof(IntBucket));
  f = malloc(sizeof(IntBucket));
  g = malloc(sizeof(IntBucket));

  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);

  a->p = 99;
  b->p = 8;
  c->p = 7;
  d->p = 100;
  e->p = 101;
  f->p = 75;
  g->p = 90;

  avl_tree_insert ( t, a );
  ASSERT (t->root->count == 1, "Wrong count of children.");
  ASSERT (t->root->height == 1, "Root with no children has wrong height.");
  ASSERT (t->root->balance_factor == 0, "Root with no children has wrong balance factor.");

  avl_tree_insert ( t, b );
  ASSERT (t->root->count == 2, "Wrong count of children in root after inserting one child.");
  ASSERT (t->root->height == 2, "Wrong height for root with one child.");
  ASSERT (t->root->balance_factor == 1, "Root with one child has wrong balance factor.");
  ASSERT (t->root->left->count == 1, "Child has wrong count.");
  ASSERT (t->root->left->height == 1, "Child has wrong height.");
  ASSERT (t->root->left->balance_factor == 0, "Node with no children has wrong balance factor.");
  ASSERT (t->root->left->parent == t->root, "Left child has wrong parent after first insert.");

  ASSERT ( ((IntBucket*)(t->root->bucket))->p == 99, "Wrong value for root" );
  ASSERT ( ((IntBucket*)(t->root->left->bucket))->p == 8, "Wrong value for left child" );

  avl_tree_insert(t,c); // ROOT->LEFT->LEFT, should get balance
  ASSERT ( ((IntBucket*)(t->root->bucket))->p == 8, "Wrong root after insert requiring rotate");
  ASSERT ( ((IntBucket*)(t->root->right->bucket))->p == 99, "Wrong root after insert requiring rotate");
  ASSERT ( ((IntBucket*)(t->root->left->bucket))->p == 7, "Wrong root after insert requiring rotate");

  ASSERT (t->root->left->parent == t->root, "Left has wrong parent after rebalance.");
  ASSERT (t->root->right->parent == t->root, "Right has wrong parent after rebalance.");

  ASSERT(t->root->count==3, "Wrong count of children at root after 2nd insert");
  ASSERT(t->root->height==2, "Wrong height after 2nd insert");
  ASSERT(t->root->balance_factor==0, "Wrong balance factor after 2nd insert");
  ASSERT(t->root->left->count==1, "Wrong child count after 2nd insert");
  ASSERT(t->root->left->height==1, "Wrong child height after 2nd insert");
  ASSERT(t->root->left->balance_factor==0, "Wrong child balance factor after 2nd insert");

  avl_tree_insert(t,d);
  ASSERT(t->root->balance_factor == -1, "Wrong balance");
  avl_tree_insert(t,e);
  ASSERT(t->root->balance_factor == -1, "Wrong balance");
  ASSERT(t->root->height == 3, "Wrong height");
  avl_tree_insert(t,f);
  avl_tree_insert(t,g);
  ASSERT(t->root->count == 7, "wrong count");

  destroy_avl_tree(t);

  free(g);
  free(f);
  free(e);
  free(d);
  free(c);
  free(b);
  free(a);
}

void btnode_initialize_destroy ( void )
{
  BTNode * b = init_btnode(sizeof(IntBucket));

  ASSERT ( b->left == NULL, "left is not null" );
  ASSERT ( b->right == NULL, "right is not null" );
  ASSERT ( b->bucket != NULL, "bucket is null!" );

  destroy_btnode(b);
}

void avl_tree_bst_helpers ( void )
{
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);

  IntBucket *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k;

  a = malloc(sizeof(IntBucket));
  b = malloc(sizeof(IntBucket));
  c = malloc(sizeof(IntBucket));
  d = malloc(sizeof(IntBucket));
  e = malloc(sizeof(IntBucket));
  f = malloc(sizeof(IntBucket));
  g = malloc(sizeof(IntBucket));
  h = malloc(sizeof(IntBucket));
  i = malloc(sizeof(IntBucket));
  j = malloc(sizeof(IntBucket));
  k = malloc(sizeof(IntBucket));

  a->p = 99;
  b->p = 8;
  c->p = 33;
  d->p = 17;
  e->p = 86;
  f->p = 87;
  g->p = 93;
  h->p = 17;
  i->p = 150;
  j->p = 155;
  k->p = 140;

  bst_insert(t,a);
  ASSERT(t->root->count == 1, "Wrong count.");
  ASSERT(t->root->height == 1, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor == 0, "Wrong balance factor.");
  ASSERT(t->root->left == NULL, "Left not NULL");
  ASSERT(t->root->right == NULL, "Right not NULL");

  bst_insert(t,b);
  ASSERT(t->root->count == 2, "Wrong count.");
  ASSERT(t->root->height == 2, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor == 1, "Wrong balance factor.");
  ASSERT(t->root->right == NULL, "Right not NULL");
  ASSERT(t->root->left != NULL, "Left NULL");
  ASSERT(t->root->left->count == 1, "Wrong count.");
  ASSERT(t->root->left->height == 1, "Wrong height.");
  ASSERT(t->root->left->left == NULL, "Left not NULL.");
  ASSERT(t->root->left->right == NULL, "Right not NULL.");

  bst_insert(t,c);
  ASSERT(t->root->count == 3, "Wrong count.");
  ASSERT(t->root->height == 3, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 2, "Wrong balance factor.");

  bst_insert(t,d);
  ASSERT(t->root->count == 4, "Wrong count.");
  ASSERT(t->root->height == 4, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 3, "Wrong balance factor.");

  bst_insert(t,e);
  ASSERT(t->root->count == 5, "Wrong count.");
  ASSERT(t->root->height == 4, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 3, "Wrong balance factor.");

  bst_insert(t,f);
  ASSERT(t->root->count == 6, "Wrong count.");
  ASSERT(t->root->height == 5, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 4, "Wrong balance factor.");

  bst_insert(t,g);
  ASSERT(t->root->count == 7, "Wrong count.");
  ASSERT(t->root->height == 6, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 5, "Wrong balance factor.");

  bst_insert(t,h);
  ASSERT(t->root->count == 8, "Wrong count.");
  ASSERT(t->root->height == 6, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 4, "Wrong balance factor.");

  bst_insert(t,i);
  ASSERT(t->root->count == 9, "Wrong count.");
  ASSERT(t->root->height == 6, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 3, "Wrong balance factor.");

  bst_insert(t,j);
  ASSERT(t->root->count == 10, "Wrong count.");
  ASSERT(t->root->height == 6, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 3, "Wrong balance factor.");

  bst_insert(t,k);
  ASSERT(t->root->count == 11, "Wrong count.");
  ASSERT(t->root->height == 6, "Wrong height.");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity.");
  ASSERT(t->root->balance_factor = 3, "Wrong balance factor.");

  free(k);
  free(j);
  free(i);
  free(h);
  free(g);
  free(f);
  free(e);
  free(d);
  free(c);
  free(b);
  free(a);

  destroy_avl_tree(t);
}

void avl_tree_insert_many ( void )
{
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);

  int insert_qty = 13;

  IntBucket ib[] = {
    {30272}, {16274}, {11768}, {10231}, {28474}, { 7272}, {15032}, {13196}, {29825}, { 6840},
    {18444}, {18793}, {13786}, {21125}, {25311}, {23414}, {18374}, {24110}, {15465}, {26300},
    { 1181}, { 6297}, { 3693}, {20957}, {22585}, { 8915}, {30371}, { 2036}, {18499}, {18391},
    {15360}, {32509}, {23336}, {18848}, {25712}, { 6162}, { 1483}, { 4309}, {13482}, {14809},
    { 5596}, {22524}, {13958}, {16918}, {25668}, {31621}, {30060}, {24637}, {28116}, {15994},
    {30595}, {30642}, {30017}, { 7221}, { 2916}, { 7010}, {29356}, {22282}, {30649}, {17493},
    {28780}, { 6725}, {26998}, {28805}, {24689}, {25547}, {17625}, {14250}, {11250}, {16195},
    { 9542}, {26029}, { 2734}, {23373}, {21176}, {28102}, { 1894}, {  325}, { 9406}, { 4915},
    { 8759}, {32413}, {14144}, { 5394}, { 3495}, {32030}, {23904}, { 4260}, {11579}, {11100},
    {27212}, {20562}, {30264}, {30850}, {22393}, {28107}, {21299}, {25306}, { 2668}, { 3894},
  };

  int i;

  /*
  avl_tree_insert(t, ib+0);
  ASSERT( ((IntBucket*)t->root->bucket)->p == 30272, "Wrong value in root after first insert");
  ASSERT(t->root->count == 1, "Wrong count after first insert");
  ASSERT(t->root->height == 1, "Wrong height after first insert");
  ASSERT(t->root->balance_factor == 0, "Wrong balance factor after first insert");
  ASSERT(t->root->multiplicity == 1, "Wrong multiplicity after first insert");
  ASSERT(t->root->left == NULL, "Left not NULL after first insert");
  ASSERT(t->root->right == NULL, "Right not NULL after first insert");
  ASSERT(t->root->parent == NULL, "Root node parent not NULL");
  ASSERT(avl_verify_consistency(t->root)==true, "Tree inconsistent after inserting");

  avl_tree_insert(t, ib+1);
  ASSERT( ((IntBucket*)t->root->bucket)->p == 30272, "Wrong value in root after second insert");
  ASSERT( ((IntBucket*)t->root->left->bucket)->p == 16274, "Wrong value in root after second insert");
  ASSERT(t->root->count == 2, "Wrong count after second insert");
  ASSERT(t->root->height == 2, "Wrong height after second insert");
  ASSERT(t->root->balance_factor == 1, "Wrong balance factor after second insert");
  ASSERT(t->root->left != NULL, "no left child after second insert");
  ASSERT(t->root->right == NULL, "right child exists after second insert");
  ASSERT(t->root->left->parent == t->root, "Left child has wrong parent after second insert");
  ASSERT(avl_verify_consistency(t->root)==true, "Tree inconsistent after inserting");
  */

  for (i = 0; i < insert_qty; i += 1) {
    avl_tree_insert(t, &(ib[i]));
    // fprintf(stderr, "%d: %d\n", i, ib[i].p);
    ASSERT(avl_verify_consistency(t->root)==true, "Tree inconsistent after inserting");
  }

  ASSERT(t->root->height == 5, "Wrong height after 13 inserts");
  ASSERT(t->root->balance_factor = 1, "Wrong balance factor after 13 inserts");
  ASSERT(t->root->count == 13, "Wrong count after 13 inserts");
  ASSERT( ((IntBucket*)t->root->left->bucket)->p == 10231, "Wrong");
  ASSERT( ((IntBucket*)t->root->left->left->bucket)->p == 7272, "Wrong");
  ASSERT( ((IntBucket*)t->root->left->left->left->bucket)->p == 6840, "Wrong");
  ASSERT( ((IntBucket*)t->root->left->right->bucket)->p == 13196, "Wrong");
  ASSERT( ((IntBucket*)t->root->left->right->left->bucket)->p == 11768, "Wrong");
  ASSERT( ((IntBucket*)t->root->left->right->right->bucket)->p == 15032, "Wrong");
  ASSERT( ((IntBucket*)t->root->left->right->right->left->bucket)->p == 13786, "Wrong");

  ASSERT( ((IntBucket*)t->root->right->bucket)->p == 29825, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->left->bucket)->p == 18793, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->left->left->bucket)->p == 18444, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->left->right->bucket)->p == 28474, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->right->bucket)->p == 30272, "Wrong");

  avl_tree_insert(t, ib+i);
  ASSERT( ((IntBucket*)t->root->right->bucket)->p == 28474, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->left->bucket)->p == 18793, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->left->left->bucket)->p == 18444, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->left->right->bucket)->p == 21125, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->right->bucket)->p == 29825, "Wrong");
  ASSERT( ((IntBucket*)t->root->right->right->right->bucket)->p == 30272, "Wrong");

  ASSERT(avl_verify_consistency(t->root) == true, "Inconsistent after insert 14");

  for (; i < 100; i += 1) {
    avl_tree_insert(t, &(ib[i]));
    // fprintf(stderr, "%d: %d\n", i, ib[i].p);
    ASSERT(avl_verify_consistency(t->root)==true, "Tree inconsistent after inserting");
  }

  destroy_avl_tree(t);
}

void avl_tree_insert_random ( void ) {
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);
  IntBucket bucket;

  int i;

  srand(12345678);

  for ( i = 0; i < 100000; i += 1 ) {
    bucket.p = rand();
    avl_tree_insert(t, &bucket);
    ASSERT(t->root->count == i+1, "Wrong count after insert");
  }
  ASSERT(avl_verify_consistency(t->root)==true, "Tree inconsistent after insert");

  destroy_avl_tree(t);
}

_Bool doit(BTNode * cur) {
  fprintf(stderr, "traverse: %d\n", ((IntBucket*)cur->bucket)->p);
  return true;
}

void avl_tree_traverse_test ( void ) {
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);
  IntBucket bucket;

  int i;

  srand(12345678);

  for ( i = 0; i < 1000; i += 1 ) {
    bucket.p = rand();
    avl_tree_insert(t, &bucket);
  }

  avl_tree_traverse(t, doit);

  destroy_avl_tree(t);
}

void avl_tree_find_median ( void ) {
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);
  IntBucket * median;

  IntBucket ib[] = {
    {30272}, {16274}, {11768}, {10231}, {28474}, { 7272}, {15032}, {13196}, {29825}, { 6840},
    {18444}, {18793}, {13786}, {21125}, {25311}, {23414}, {18374}, {24110}, {15465}, {26300},
    { 1181}, { 6297}, { 3693}, {20957}, {22585}, { 8915}, {30371}, { 2036}, {18499}, {18391},
    {15360}, {32509}, {23336}, {18848}, {25712}, { 6162}, { 1483}, { 4309}, {13482}, {14809},
    { 5596}, {22524}, {13958}, {16918}, {25668}, {31621}, {30060}, {24637}, {28116}, {15994},
    {30595}, {30642}, {30017}, { 7221}, { 2916}, { 7010}, {29356}, {22282}, {30649}, {17493},
    {28780}, { 6725}, {26998}, {28805}, {24689}, {25547}, {17625}, {14250}, {11250}, {16195},
    { 9542}, {26029}, { 2734}, {23373}, {21176}, {28102}, { 1894}, {  325}, { 9406}, { 4915},
    { 8759}, {32413}, {14144}, { 5394}, { 3495}, {32030}, {23904}, { 4260}, {11579}, {11100},
    {27212}, {20562}, {30264}, {30850}, {22393}, {28107}, {21299}, {25306}, { 2668}, { 3894},
  };

  int i;

  for ( i = 0; i < 100; i += 1 ) {
    avl_tree_insert(t, ib+i);
  }

  median = (IntBucket*)(avl_tree_get_median(t)->bucket);
  ASSERT(median->p == 18391, "Wrong median!");

  destroy_avl_tree(t);
}

void avl_tree_test_delete ( void ) {
  AVLTree * t = init_avl_tree(sizeof(IntBucket), &bucket_int_compare);
  BTNode * median_node;
  IntBucket x;

  /*
  IntBucket ib[] = {
    {30272}, {16274}, {11768}, {10231}, {28474}, { 7272}, {15032}, {13196}, {29825}, { 6840},
    {18444}, {18793}, {13786}, {21125}, {25311}, {23414}, {18374}, {24110}, {15465}, {26300},
    { 1181}, { 6297}, { 3693}, {20957}, {22585}, { 8915}, {30371}, { 2036}, {18499}, {18391},
    {15360}, {32509}, {23336}, {18848}, {25712}, { 6162}, { 1483}, { 4309}, {13482}, {14809},
    { 5596}, {22524}, {13958}, {16918}, {25668}, {31621}, {30060}, {24637}, {28116}, {15994},
    {30595}, {30642}, {30017}, { 7221}, { 2916}, { 7010}, {29356}, {22282}, {30649}, {17493},
    {28780}, { 6725}, {26998}, {28805}, {24689}, {25547}, {17625}, {14250}, {11250}, {16195},
    { 9542}, {26029}, { 2734}, {23373}, {21176}, {28102}, { 1894}, {  325}, { 9406}, { 4915},
    { 8759}, {32413}, {14144}, { 5394}, { 3495}, {32030}, {23904}, { 4260}, {11579}, {11100},
    {27212}, {20562}, {30264}, {30850}, {22393}, {28107}, {21299}, {25306}, { 2668}, { 3894},
  };

  int i;

  for ( i = 0; i < 100; i += 1 ) {
    avl_tree_insert(t, ib+i);
  }
  ASSERT(avl_verify_consistency(t->root), "Tree starting inconsistent.");

  median_node = avl_tree_get_median(t);
  avl_delete_node(median_node);
  ASSERT(avl_verify_consistency(t->root), "Tree inconsistent after delete.");
  median_node = avl_tree_get_median(t);
  fprintf(stderr, "New median: %d\n", ((IntBucket*)(median_node->bucket))->p);
  ASSERT( ((IntBucket*)(median_node->bucket))->p == 18374, "Wrong median after delete." );

  while ( t->root->count > 5 ) {
    fprintf(stderr, "Deleting %d\n", ((IntBucket*)(t->root->bucket))->p);
    avl_delete_node(t->root);
    ASSERT(avl_verify_consistency(t->root), "Tree inconsistent after delete.");
  }
  */

  x.p = 99; avl_tree_insert(t, &x);
  x.p = 150; avl_tree_insert(t, &x);
  x.p = 151; avl_tree_insert(t, &x);
  ASSERT(((IntBucket*)(t->root->bucket))->p == 150, "Wrong root value.");
  ASSERT(avl_verify_consistency(t->root), "Tree inconsistent after three inserts.");
  ASSERT(t->root->count == 3, "Wrong number of nodes after delete.");

  avl_delete_node(t->root->right);
  ASSERT(((IntBucket*)(t->root->bucket))->p == 150, "Wrong root value after first delete.");
  ASSERT(avl_verify_consistency(t->root), "Tree inconsistent after first delete.");
  ASSERT(t->root->count == 2, "Wrong number of nodes after first delete.");

  avl_delete_node(t->root->left);
  ASSERT(((IntBucket*)(t->root->bucket))->p == 150, "Wrong root value after second delete.");
  ASSERT(avl_verify_consistency(t->root), "Tree inconsistent after second delete.");
  fprintf(stderr, "New count: %d\n", t->root->count);
  ASSERT(t->root->count == 1, "Wrong number of nodes after second delete.");

  destroy_avl_tree(t);
}

void do_tests ( void )
{
  TEST ( sanity_check_zero );
  TEST ( avl_bucket_int_compare );
  TEST ( btnode_initialize_destroy );
  TEST ( avl_tree_init_destroy );
  TEST ( avl_tree_bst_helpers );
  TEST ( avl_tree_insert_elements );
  TEST ( avl_tree_insert_many );
  // TEST ( avl_tree_insert_random );
  // TEST ( avl_tree_traverse_test );
  TEST ( avl_tree_find_median );
  TEST ( avl_tree_test_delete );
}

