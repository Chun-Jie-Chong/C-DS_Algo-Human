#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/binary_search_tree.c"

// Test case for inserting a node
void testInsert()
{
    node *root = NULL;
    root = insert(root, 50);
    CU_ASSERT_PTR_NOT_NULL(root);
    CU_ASSERT_EQUAL(root->data, 50);

    root = insert(root, 30);
    CU_ASSERT_PTR_NOT_NULL(root->left);
    CU_ASSERT_EQUAL(root->left->data, 30);

    root = insert(root, 20);
    CU_ASSERT_PTR_NOT_NULL(root->left->left);
    CU_ASSERT_EQUAL(root->left->left->data, 20);

    root = insert(root, 40);
    CU_ASSERT_PTR_NOT_NULL(root->left->right);
    CU_ASSERT_EQUAL(root->left->right->data, 40);

    root = insert(root, 70);
    CU_ASSERT_PTR_NOT_NULL(root->right);
    CU_ASSERT_EQUAL(root->right->data, 70);

    root = insert(root, 60);
    CU_ASSERT_PTR_NOT_NULL(root->right->left);
    CU_ASSERT_EQUAL(root->right->left->data, 60);

    root = insert(root, 80);
    CU_ASSERT_PTR_NOT_NULL(root->right->right);
    CU_ASSERT_EQUAL(root->right->right->data, 80);
}

// Test case for deleting a node
void testDelete()
{
    node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    root = delete(root, 30);

    root = delete(root, 20);
    CU_ASSERT_EQUAL(find(root, 20), 0);

    root = delete(root, 30);
    CU_ASSERT_EQUAL(find(root, 30), 0);

    root = delete(root, 50);
    CU_ASSERT_EQUAL(find(root, 50), 0);
}

// Test case for searching a node
void testFind()
{
    node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Assert the search results
    CU_ASSERT_EQUAL(find(root, 40), 1);
    CU_ASSERT_EQUAL(find(root, 50), 1);
    CU_ASSERT_EQUAL(find(root, 90), 0);
}

// Test case for listing the nodes in order
void testInOrderTraversal()
{
    node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Redirect stdout to a file for capturing the output
    freopen("output.txt", "w", stdout);

    // Call the inOrder function to print the nodes
    inOrder(root);

    // Close the file
    fclose(stdout);

    // Assert the output
    FILE *file = fopen("output.txt", "r");
    char output[100];
    fgets(output, sizeof(output), file);
    fclose(file);
    CU_ASSERT_STRING_EQUAL(output, "\t[ 50 ]\t\t[ 30 ]\t\t[ 20 ]\t\t[ 40 ]\t\t[ 70 ]\t\t[ 60 ]\t\t[ 80 ]\t");
}
// Main function
int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("BinarySearchTree_Test_Suite", 0, 0);
    CU_add_test(suite, "Test Insert", testInsert);
    CU_add_test(suite, "Test Delete", testDelete);
    CU_add_test(suite, "Test Find", testFind);
    // CU_add_test(suite, "Test In-Order Traversal", testInOrderTraversal);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}