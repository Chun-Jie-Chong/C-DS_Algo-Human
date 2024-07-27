#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/hash_set.c"

void testAddAndContains() {
    hash_set_t* set = init_hash_set();
    
    int a = 5;
    int b = 10;
    int c = 15;
    int d = 20;

    add(set, &a);
    add(set, &b);
    add(set, &c);

    CU_ASSERT_TRUE(contains(set, &a));
    CU_ASSERT_TRUE(contains(set, &b));
    CU_ASSERT_TRUE(contains(set, &c));
    CU_ASSERT_FALSE(contains(set, &d));
}

void testRemove() {
    hash_set_t* set = init_hash_set();
    
    int a = 5;
    int b = 10;
    int c = 15;
    int d = 20;

    add(set, &a);
    add(set, &b);
    add(set, &c);

    delete(set, &b);

    CU_ASSERT_TRUE(contains(set, &a));
    CU_ASSERT_FALSE(contains(set, &b));
    CU_ASSERT_TRUE(contains(set, &c));
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("HashSet_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Add and Contains Test", testAddAndContains);
    CU_add_test(suite, "Remove Test", testRemove);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}