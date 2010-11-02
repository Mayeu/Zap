#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "test.h"

/*
 * The suite initialization function.  * Opens the temporary file used by
 * the tests.  * Returns zero on success, non-zero otherwise.  
 */
int
init_suite1(void)
{
    return 0;
}

/*
 * The suite cleanup function. Closes the temporary file used by the
 * tests. Returns zero on success, non-zero otherwise. 
 */
int
clean_suite1(void)
{
    return 0;
}

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
    pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /*
     * Add test for the point 
     */
    test_zpts(pSuite);

    /*
     * Run all tests using the CUnit Basic interface 
     */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
