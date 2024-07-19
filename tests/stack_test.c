#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/stack.c"

// Test case to check if the stack is empty after creation
void testIsEmptyAfterCreation() {
    initStack();
    CU_ASSERT_TRUE(isEmpty());
}

// Test case to check the size of the stack after pushing elements
void testSizeAfterPush() {
     initStack();

    int a = 10;
    int b = 20;
    int c = 30;

    push(&a);
    push(&b);
    push(&c);
    CU_ASSERT_EQUAL(size(), 2);
}

void testTopAfterPush() {
    initStack();

    int a = 10;
    int b = 20;
    int c = 30;

    push(&a);
    push(&b);
    push(&c);

    CU_ASSERT_EQUAL(*(int*)top(), 30);
}


void testIsEmptyAfterPop() {
    initStack();

    int a = 10;
    int b = 20;
    int c = 30;

    push(&a);
    push(&b);
    push(&c);

    pop();
    pop();
    pop();

    CU_ASSERT_TRUE(isEmpty());

}

void testPop() {
    initStack();

    int a = 10;
    int b = 20;
    int c = 30;

    push(&a);
    push(&b);
    push(&c);

    CU_ASSERT_EQUAL(*(int*)pop(), 30);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("MergeSort_Test_Suite", 0, 0);
    CU_add_test(suite, "Test if stack is empty after creation", testIsEmptyAfterCreation);
    CU_add_test(suite, "Test size of stack after pushing elements", testSizeAfterPush);
    CU_add_test(suite, "Test top element after pushing elements", testTopAfterPush);
    CU_add_test(suite, "Test if stack is empty after popping all elements", testIsEmptyAfterPop);
    CU_add_test(suite, "Test popped element", testPop);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}