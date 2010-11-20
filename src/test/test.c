/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <mayeu.tik@gmail.com> and <pierrealain.toret@gmail.com> wrote this file. As
 * long as you retain this notice you can do whatever you want with this stuff.
 * If we meet some day, and you think this stuff is worth it, you can buy us a
 * beer in return. Matthieu Maury & Pierre-Alain Toret
 * ----------------------------------------------------------------------------
 */

/**
 * @file test.c
 * @brief Main file for launching the test
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/13
 */

/*
 * Include
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "test.h"

/*
 * Define
 */

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

   test_zcrvw();
    test_zpts();
    test_zops();

    /*
     * Run all tests using the CUnit Basic interface 
     */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
