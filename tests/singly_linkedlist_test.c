#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/singly_linkedlist.c"

void testInsertion()
{
    // Insert at position 1
    insert(1, 1);
    CU_ASSERT_EQUAL(start->info, 1);
    CU_ASSERT_PTR_NULL(start->link);
    
    // Insert at position 2
    insert(2, 2);
    CU_ASSERT_EQUAL(start->link->info, 2);
    CU_ASSERT_PTR_NULL(start->link->link);
    
    // Insert at position 3
    insert(3, 3);
    CU_ASSERT_EQUAL(start->link->link->info, 3);
    CU_ASSERT_PTR_NULL(start->link->link->link);
    
    // Insert at position 2
    insert(2, 4);
    CU_ASSERT_EQUAL(start->link->info, 4);
    CU_ASSERT_EQUAL(start->link->link->info, 2);
    CU_ASSERT_EQUAL(start->link->link->link->info, 3);
    CU_ASSERT_PTR_NULL(start->link->link->link->link);
}

void testDeletion()
{
    // Insert nodes for deletion
    insert(1, 1);
    insert(2, 2);
    insert(3, 3);
    insert(2, 4);
    // 1 ->4 ->2 ->3 ->NULL
    // Delete at position 3
    // 1 ->4 ->3 ->NULL
    deletion(3);
    CU_ASSERT_EQUAL(start->info, 1);
    CU_ASSERT_EQUAL(start->link->info, 4);
    CU_ASSERT_EQUAL(start->link->link->info, 3);
    
    // Delete at position 1
    // 4 ->3 ->NULL
    deletion(1);
    CU_ASSERT_EQUAL(start->info, 4);
    CU_ASSERT_EQUAL(start->link->info, 3);
}

// void testViewList()
// {
//     // Test viewing an empty list
//     start = NULL;
//     CU_ASSERT_EQUAL(viewlist(), NULL);

//     // Test viewing a non-empty list
//     insert(1, 39);
//     insert(2, 10);
//     insert(3, 11);
//     CU_ASSERT_EQUAL(viewlist(), "39 10 11");
// }

int main() {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("SinglyLinkedList_Test_Suite", NULL, NULL);
    CU_add_test(suite, "testInsertion", testInsertion);
    CU_add_test(suite, "testDeletion", testDeletion);
    // CU_add_test(suite, "testViewList", testViewList);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    CU_cleanup_registry();
    
    return CU_get_error();
}