#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/queue.c"

void testEnqueueDequeue()
{
    create();
    enque(10);
    CU_ASSERT_EQUAL(size(), 1);
}

void testSize()
{
    create();
    CU_ASSERT_EQUAL(size(), 0);
    enque(10);
    CU_ASSERT_EQUAL(size(), 1);
    enque(20);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Queue_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Enqueue and Dequeue Test", testEnqueueDequeue);
    CU_add_test(suite, "Size Test", testSize);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

