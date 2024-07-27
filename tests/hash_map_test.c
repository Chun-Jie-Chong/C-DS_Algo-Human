#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/hash_map.c"

typedef struct data_struct_s
{
    char key[256];
    int value;
} data_struct_t;

void testHashMap() {
    map_t map = hashmap_new();
    CU_ASSERT_PTR_NOT_NULL(map);

    // Test insertion
    data_struct_t* entry1 = malloc(sizeof(data_struct_t));
    strcpy(entry1->key, "key1");
    entry1->value = 100;
    CU_ASSERT_EQUAL(hashmap_put(map, entry1->key, entry1), MAP_OK);

    data_struct_t* entry2 = malloc(sizeof(data_struct_t));
    strcpy(entry2->key, "key2");
    entry2->value = 200;
    CU_ASSERT_EQUAL(hashmap_put(map, entry2->key, entry2), MAP_OK);

    data_struct_t* entry3 = malloc(sizeof(data_struct_t));
    strcpy(entry3->key, "key3");
    entry3->value = 300;
    CU_ASSERT_EQUAL(hashmap_put(map, entry3->key, entry3), MAP_OK);

    // Test lookup
    CU_ASSERT_EQUAL(hashmap_get(map, entry1->key, (void**)(&entry1)), MAP_OK);

    data_struct_t* entry4 = malloc(sizeof(data_struct_t));
    strcpy(entry4->key, "key4");
    entry4->value = 400;
    CU_ASSERT_EQUAL(hashmap_get(map, entry4->key, (void**)(entry4)), MAP_MISSING);

    // Test deletion
    hashmap_remove(map, entry2 -> key);
    CU_ASSERT_EQUAL(hashmap_get(map, entry2 -> key, (void**)(&entry2)), MAP_MISSING);

    hashmap_free(map);

}

void test_hashmap_new() {
    map_t map = hashmap_new();
    CU_ASSERT_PTR_NOT_NULL(map);
    hashmap_free(map);
}

void test_hashmap_put_get() {
    map_t map = hashmap_new();
    CU_ASSERT_PTR_NOT_NULL(map);

    char* key = "test_key";
    int value = 42;

    int result = hashmap_put(map, key, &value);
    CU_ASSERT_EQUAL(result, MAP_OK);

    int retrieved_value = hashmap_get(map, key, (void**)(&value));
    CU_ASSERT_EQUAL(retrieved_value, MAP_OK);

    hashmap_free(map);
}

void test_hashmap_remove() {
    map_t map = hashmap_new();
    CU_ASSERT_PTR_NOT_NULL(map);

    data_struct_t* entry = malloc(sizeof(data_struct_t));
    strcpy(entry->key, "test_key");
    entry->value = 42;

    int result = hashmap_put(map, entry->key, entry);
    CU_ASSERT_EQUAL(result, MAP_OK);

    int retrieved_value = hashmap_get(map, entry -> key, (void**)(&entry));
    CU_ASSERT_EQUAL(retrieved_value, MAP_OK);

    result = hashmap_remove(map, entry -> key);
    CU_ASSERT_EQUAL(result, MAP_OK);

    retrieved_value = hashmap_get(map, entry -> key, (void**)(&entry));
    CU_ASSERT_EQUAL(retrieved_value, MAP_MISSING);

    hashmap_free(map);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("HashMap_Test_Suite", NULL, NULL);
    CU_add_test(suite, "testHashMap", testHashMap);
    // CU_add_test(suite, "test_hashmap_new", test_hashmap_new);
    // CU_add_test(suite, "test_hashmap_put_get", test_hashmap_put_get);
    // CU_add_test(suite, "test_hashmap_remove", test_hashmap_remove);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}