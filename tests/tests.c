#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "wows-splash.h"

void test_wows_parse_splash_fp(void) {
    wows_splash *splash_content = NULL;

    int ret = wows_parse_splash("tests/test_splash.bin", &splash_content);

    CU_ASSERT_EQUAL(ret, 0);
    CU_ASSERT_PTR_NOT_NULL(splash_content);
    CU_ASSERT_EQUAL(splash_content->entry_count, 2);
    CU_ASSERT_PTR_NOT_NULL(splash_content->entry_map);
    CU_ASSERT_PTR_NOT_NULL(splash_content->entries);
    CU_ASSERT_EQUAL(splash_content->entries[0]->name_len, 5);
    CU_ASSERT_STRING_EQUAL(splash_content->entries[0]->name, "hello");
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[0]->x, 1.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[0]->y, 2.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[0]->z, 3.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[0]->dx, 0.1, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[0]->dy, 0.2, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[0]->dz, 0.3, 0.001);
    CU_ASSERT_EQUAL(splash_content->entries[1]->name_len, 5);
    CU_ASSERT_STRING_EQUAL(splash_content->entries[1]->name, "world");
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[1]->x, 4.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[1]->y, 5.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[1]->z, 6.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[1]->dx, 0.4, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[1]->dy, 0.5, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(splash_content->entries[1]->dz, 0.6, 0.001);

    // TODO add more assertions to cover error cases

    wows_splash_print(splash_content);
    wows_splash_free(splash_content);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("wows_parse_splash", NULL, NULL);
    CU_add_test(suite, "test_wows_parse_splash_fp", test_wows_parse_splash_fp);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
