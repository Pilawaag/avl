#include <avl.h>

node_t *init_node(const void *data)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = (void *) data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

tree_t *init_tree(cmp_data_f cmp_data, print_data_f print_data, free_data_f free_data)
{
    tree_t *tree =  malloc(sizeof(tree_t));
    tree->root = NULL;
    tree->cmp_data = cmp_data;
    tree->print_data = print_data;
    tree->free_data = free_data;
    return tree;
}

int height(node_t *node)
{
    if(NULL == node)
    {
        return 0;
    }

    return node->height;
}

int get_max_height(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int get_balance(node_t *node)
{
    if(NULL == node)
    {
        return 0;
    }

    return height(node->left) - height(node->right);
}

node_t *min_value_node(node_t *node)
{
    node_t *curr = node;

    while(NULL != curr->left)
    {
        curr = curr->left;
    }

    return curr;
}

node_t *rotate_right(node_t *node)
{
    node_t *temp_one = node->left;
    node_t *temp_two = temp_one->right;

    temp_one->right = node;
    node->left = temp_two;

    temp_one->height = get_max_height(height(temp_one->left), height(temp_one->right)) + 1;
    node->height = get_max_height(height(node->left), height(node->right)) + 1;

    return temp_one;
}

node_t *rotate_left(node_t *node)
{
    node_t *temp_one = node->right;
    node_t *temp_two = temp_one->left;

    temp_one->left = node;
    node->right = temp_two;

    temp_one->height = get_max_height(height(temp_one->left), height(temp_one->right)) + 1;
    node->height = get_max_height(height(node->left), height(node->right)) + 1;

    return temp_one;
}

status_t add_data_to_tree(tree_t *tree, const void *data)
{
    if(NULL == tree->root)
    {
        tree->root = init_node(data);
        return 0;
    }
 
    node_t *new_root = insert_data(tree, tree->root, data);

    if(NULL != new_root)
    {
        tree->root = new_root;
        return 0;
    }

    return -1;
}

status_t rm_data_from_tree(tree_t *tree, const void *data)
{
    if(NULL == tree->root)
    {
        return -1;
    }

    node_t *new_root = remove_data(tree, tree->root, data);

    if(NULL != new_root)
    {
        tree->root = new_root;
        return 0;
    }

    return -1;
}

node_t *insert_data(tree_t *tree, node_t *node, const void *data)
{
    if(NULL == node)
    {
        return init_node(data);
    }

    int retval = tree->cmp_data(data, node->data);

    if(retval < 0)
    {
        node->left = insert_data(tree, node->left, data);
    }
    else if(retval > 0)
    {
        node->right = insert_data(tree, node->right, data);
    }
    else
    {
        return node;
    }

    int balance = get_balance(node);    

    if(balance > 1 && tree->cmp_data(data, node->left->data) < 0)
    {
        return rotate_right(node);
    }

    if(balance < -1 && tree->cmp_data(data, node->right->data) > 0)
    {
        return rotate_left(node);
    }

    if(balance > 1 && tree->cmp_data(data, node->left->data) > 0)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if(balance < -1 && tree->cmp_data(data, node->right->data) < 0)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    node->height = get_max_height(height(node->left), 
                                  height(node->right)) + 1;

    return node;
}

node_t *remove_data(tree_t *tree, node_t *node, const void *data)
{
    if(NULL == node)
    {
        return node;
    }

    int retval = tree->cmp_data(data, node->data);

    if(retval < 0)
    {
        node->left = remove_data(tree, node->left, data);
    }
    else if(retval > 0)
    {
        node->right = remove_data(tree, node->right, data);
    }
    else
    {
        if(NULL == node->left || NULL == node->right)
        {
            node_t *temp = node->left ? node->left : node->right;

            if(NULL == temp)
            {
                temp = node;
                node = NULL;
                tree->free_data(temp->data);
            }
            else
            {
                tree->free_data(node->data);
                node->data = temp->data;
                node->left = temp->left;
                node->right = temp->right;
                node->height = temp->height;
            }

            free(temp);
        }
        else
        {
            node_t *temp = min_value_node(node->right);
            tree->free_data(node->data);
            node->data = temp->data;
            node->right = remove_data(tree, temp->right, temp->data);
        }
    }

    if(NULL == node)
    {
        return node;
    }

    int balance = get_balance(node);    

    if(balance > 1 && get_balance(node->left) >= 0)
    {
        return rotate_right(node);
    }

    if(balance < -1 && get_balance(node->right) <= 0)
    {
        return rotate_left(node);
    }

    if(balance > 1 && get_balance(node->left) < 0)
    {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if(balance < -1 && get_balance(node->right) > 0)
    {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    node->height = get_max_height(height(node->left), 
                                  height(node->right)) + 1;

    return node;
}

void display_tree(tree_t *tree)
{
    if(NULL == tree)
    {
        return;
    }

    r_display_tree(tree, tree->root);
}

void r_display_tree(tree_t *tree, node_t *node)
{
    if(NULL == node)
    {
        return;
    }

    tree->print_data(node->data);
    printf("height = %d\n", node->height);
    r_display_tree(tree, node->left);
    r_display_tree(tree, node->right);
}

void destroy_tree(tree_t *tree)
{
    if(NULL == tree)
    {
        return;
    }

    r_destroy_tree(tree, tree->root);
    free(tree);
}

void r_destroy_tree(tree_t *tree, node_t *node)
{
    if(NULL == node)
    {
        return;
    }

    r_destroy_tree(tree, node->left);
    r_destroy_tree(tree, node->right);
    tree->free_data(node->data);
    free(node);
}