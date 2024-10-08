#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/red_black_tree.c"

// Test case for inserting nodes into the Red-Black Tree
void testInsertNode() {
    Node *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 40);
    insertNode(&root, 50);
    
    //     20B
    //   /    \
    // 10B      40B
    //        /   \
    //      30R     50R
    CU_ASSERT_EQUAL(root->val, 20);
    CU_ASSERT_EQUAL(root->color, 0);
    CU_ASSERT_EQUAL(root->left->val, 10);
    CU_ASSERT_EQUAL(root->left->color, 0);
    CU_ASSERT_EQUAL(root->right->val, 40);
    CU_ASSERT_EQUAL(root->right->color, 0);
    CU_ASSERT_EQUAL(root->right->right->val, 50);
    CU_ASSERT_EQUAL(root->right->right->color, 1);
    CU_ASSERT_EQUAL(root->right->left->val, 30);
    CU_ASSERT_EQUAL(root->right->left->color, 1);
    
}

// Test case for deleting nodes from the Red-Black Tree
void testDeleteNode() {
    Node *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 40);
    insertNode(&root, 50);
    
    deleteNode(&root, 20);
    deleteNode(&root, 40);
    
    CU_ASSERT_EQUAL(root->val, 30);
    CU_ASSERT_EQUAL(root->color, 0);
    CU_ASSERT_EQUAL(root->left->val, 10);
    CU_ASSERT_EQUAL(root->left->color, 0);
    CU_ASSERT_EQUAL(root->right->val, 50);
    CU_ASSERT_EQUAL(root->right->color, 0);
}

// Test case for printing the inorder traversal of the Red-Black Tree
void testPrintInorder() {
    Node *root = NULL;
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 40);
    insertNode(&root, 50);
    
    CU_ASSERT_EQUAL_FATAL(CUE_SUCCESS, CU_initialize_registry());
    CU_pSuite suite = CU_add_suite("Red-Black Tree Test Suite", NULL, NULL);
    CU_add_test(suite, "testPrintInorder", testPrintInorder);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Red_Black_Tree_Test_Suite", NULL, NULL);
    // CU_add_test(suite, "testInsertNode", testInsertNode);
    // CU_add_test(suite, "testDeleteNode", testDeleteNode);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}