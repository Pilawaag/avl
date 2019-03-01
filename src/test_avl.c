#include <test_avl.h>

int main(void)
{
    tree_t *tree;
    tree = init_tree((cmp_data_f) string_cmp, (print_data_f) string_print, (free_data_f) string_free);
    add_data_to_tree(tree, "10");
    add_data_to_tree(tree, "20");
    add_data_to_tree(tree, "30");
    add_data_to_tree(tree, "40");
    add_data_to_tree(tree, "50");
    add_data_to_tree(tree, "25");
    rm_data_from_tree(tree, "230");
    display_tree(tree);
    destroy_tree(tree);
    return 0;
}

int string_cmp(const char *lhs_data, const char *rhs_data)
{
    return strcmp(lhs_data, rhs_data);
}

void string_print(char *data)
{
    printf("%s ", data);
}

void string_free(void *data)
{
    ;
}