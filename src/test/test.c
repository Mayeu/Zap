#include <stdio.h>
#include <string.h>
#include "test_zcrvw.c"
#include "CUnit/Basic.h"

/*
 * The main() function for setting up and running the tests. Returns a
 * CUE_SUCCESS on successful running, another CUnit error code on failure. 
 */
int
main()
{
    CU_pSuite       pSuite = NULL;

    /*
     * initialize the CUnit test registry 
     */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /*
     * add a suite to the registry 
     */
    pSuite = CU_add_suite("Suite_1", void, void);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*
     * add the tests to the suite 
     */
    /*
     * NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() 
     */
    if ((NULL ==
         CU_add_test(pSuite, "test of eccrvw_create", test_eccrvw_create)
         CU_add_test(pSuite, "test of eccrvw_create", test_eccrvw_destroy))
        CU_add_test(pSuite, "test of eccrvw_create",
                    test_eccrvw_are_equals))
        )
            || (NULL == CU_add_test(pSuite, "test of fread()", testFREAD))) {
        CU_cleanup_registry();
        return CU_get_error();
        }

    /*
     * Run all tests using the CUnit Basic interface 
     */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
