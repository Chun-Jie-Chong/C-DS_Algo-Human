#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/hash_table.c"

unsigned int string_hash(void *string)
{
	/* This is the djb2 string hash function */

	unsigned int result = 5381;
	unsigned char *p;

	p = (unsigned char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result;
}

int string_equal(void *string1, void *string2)
{
	return strcmp((char *) string1, (char *) string2) == 0;
}

void test_insert_and_search() {
    HashTable *hashTable = hash_table_new(string_hash, string_equal);

    hash_table_insert(hashTable, "name", "John Doe");
    hash_table_insert(hashTable, "occupation", "Software Developer");
    hash_table_insert(hashTable, "language", "C");

    CU_ASSERT_STRING_EQUAL(hash_table_lookup(hashTable, "name"), "John Doe");
    CU_ASSERT_STRING_EQUAL(hash_table_lookup(hashTable, "occupation"), "Software Developer");
    CU_ASSERT_STRING_EQUAL(hash_table_lookup(hashTable, "language"), "C");

    hash_table_free(hashTable);
}

void test_delete() {
    HashTable *hashTable = hash_table_new(string_hash, string_equal);

    hash_table_insert(hashTable, "name", "John Doe");
    hash_table_insert(hashTable, "occupation", "Software Developer");
    hash_table_insert(hashTable, "language", "C");

    hash_table_remove(hashTable, "name");
    CU_ASSERT_EQUAL(hash_table_lookup(hashTable, "name"), HASH_TABLE_NULL);

    hash_table_free(hashTable);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("HashTable_Test_Suite", NULL, NULL);
    CU_add_test(suite, "Test Insert and Search", test_insert_and_search);
    CU_add_test(suite, "Test Delete", test_delete);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}