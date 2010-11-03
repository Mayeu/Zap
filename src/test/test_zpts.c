#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "bool.h"
#include "zcrvw.h"
#include "zpts.h"

/*
 * Global point for the tests
 */
static ecpts_t *pts1,
               *pts2;
               // *pts3 ;
static mpz_t    p,
                n,
                a4,
                a6,
                r4,
                r6,
                gx,
                gy,
                r;

static eccrvw_t *crv;

/*
 * Private functions
 */
void            test_ecpts_create();
void            test_ecpts_cpy();
void            test_ecpts_is_inf();
void            test_ecpts_are_equals();
void            test_ecpts_destroy();

/*
 * Function
 */


/*
 * The suite initialization function.  * Opens the temporary file used by
 * the tests.  * Returns zero on success, non-zero otherwise.  
 */
int
init_suite1(void)
{
    /*
     * Init the global variable
     */

    mpz_init_set_str(p,
                     "8884933102832021670310856601112383279507496491807071433260928721853918699951",
                     10);
    mpz_init_set_str(n,
                     "8884933102832021670310856601112383279454437918059397120004264665392731659049",
                     10);
    mpz_init_set_str(a4,
                     "2481513316835306518496091950488867366805208929993787063131352719741796616329",
                     10);
    mpz_init_set_str(a6,
                     "4387305958586347890529260320831286139799795892409507048422786783411496715073",
                     10);
    mpz_init_set_str(r4,
                     "5473953786136330929505372885864126123958065998198197694258492204115618878079",
                     10);
    mpz_init_set_str(r6,
                     "5831273952509092555776116225688691072512584265972424782073602066621365105518",
                     10);
    mpz_init_set_str(gx,
                     "7638166354848741333090176068286311479365713946232310129943505521094105356372",
                     10);
    mpz_init_set_str(gy,
                     "762687367051975977761089912701686274060655281117983501949286086861823169994",
                     10);
    mpz_init_set_str(r,
                     "8094458595770206542003150089514239385761983350496862878239630488323200271273",
                     10);

    crv = eccrvw_create(p, n, a4, a6, r4, r6, gx, gy, r);


    return 0;
}

/*
 * The suite cleanup function. Closes the temporary file used by the
 * tests. Returns zero on success, non-zero otherwise. 
 */
int
clean_suite1(void)
{
    /*
     * Destroy everything
     */

    ecpts_destroy(pts1);
    ecpts_destroy(pts2);
    mpz_clears(p, n, a4, a6, r4, r6, gx, gy, r);
    eccrvw_destroy(crv);

    return 0;
}

void
test_zpts()
{
    CU_pSuite       pSuite = NULL;

    /*
     * add a suite to the registry 
     */
    pSuite =
        CU_add_suite("Test suite for zpts module", init_suite1,
                     clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        // return CU_get_error();
    }


    if ((!CU_add_test(pSuite, "test of ecpts_create()", test_ecpts_create))
        || (!CU_add_test(pSuite, "test of ecpts_are_equals()",
                         test_ecpts_are_equals))
        || (!CU_add_test(pSuite, "test of ecpts_cpy()", test_ecpts_cpy))
        || (!CU_add_test(pSuite, "test of ecpts_is_inf()",
                         test_ecpts_is_inf))
        || (!CU_add_test(pSuite, "test of ecpts_destroy()",
                         test_ecpts_destroy))) {
        CU_cleanup_registry();
        // return CU_get_error();
    }

}

/*
 * Private Functions
 */

void
test_ecpts_create(void)
{
    mpz_t           x,
                    y;

    mpz_init_set_str(x, "789", 10);
    mpz_init_set_str(y, "456", 10);

    pts1 = ecpts_create(x, y, crv, false);
    CU_ASSERT(NULL != pts1);
    CU_ASSERT(0 == mpz_cmp(x, pts1->x));
    CU_ASSERT(0 == mpz_cmp(y, pts1->y));
    CU_ASSERT(0 == eccrvw_are_equals(crv, pts1->C));
    CU_ASSERT(false == pts1->inf);
}

void
test_ecpts_are_equals()
{
    CU_ASSERT(true == ecpts_are_equals(pts1, pts1));
}

void
test_ecpts_cpy()
{
    ecpts_cpy(pts2, pts1);

    CU_ASSERT(true == ecpts_are_equals(pts1, pts2));
}

void
test_ecpts_is_inf()
{
    ecpts_set_inf(pts2, true);

    CU_ASSERT(true == ecpts_is_inf(pts2));
}

void
test_ecpts_destroy()
{
}
