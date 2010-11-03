#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "test.h"

/*
 * The main() function for setting up and running the tests. Returns a
 * CUE_SUCCESS on successful running, another CUnit error code on failure. 
 */
int
main()
{

    /*
     * initialize the CUnit test registry 
     */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /*
     * Add test for the point 
     */
    test_zpts();

    /*
     * Run all tests using the CUnit Basic interface 
     */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
