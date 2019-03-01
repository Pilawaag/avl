/**
 * AVL tree implementation based on example code found at:
 * https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 * https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
 * 
 * */


#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#ifndef AVL_HEADER_H
#define AVL_HEADER_H
#include <stdlib.h>

typedef int (*cmp_data_f)(const void *lhs_data, const void *rhs_data);
typedef void (*print_data_f)(const void *data);
typedef void (*free_data_f)(void *data);

struct node
{
    void *data;
    struct node *left;
    struct node *right;
    int height;
};

struct tree
{
    struct node *root;
    cmp_data_f cmp_data;
    print_data_f print_data;
    free_data_f free_data;
};

typedef struct node node_t;
typedef struct tree tree_t;
typedef int status_t;

/* helper functions; still need to divide public/private */
int height(node_t *node);
int get_max_height(int a, int b);
int get_balance(node_t *node);
node_t *min_value_node(node_t *node);

node_t *init_node(const void *data);
tree_t *init_tree(cmp_data_f cmp_data, print_data_f print_data, free_data_f free_data);
status_t add_data_to_tree(tree_t *tree, const void *data);
node_t *insert_data(tree_t *tree, node_t *node, const void *data);
status_t rm_data_from_tree(tree_t *tree, const void *data);
node_t *remove_data(tree_t *tree, node_t *node, const void *data);
node_t *rotate_right(node_t *node);
node_t *rotate_left(node_t *node);
void display_tree(tree_t *tree);
void r_display_tree(tree_t *tree, node_t *node);
void destroy_tree(tree_t *tree);
void r_destroy_tree(tree_t *tree, node_t *node);
#endif