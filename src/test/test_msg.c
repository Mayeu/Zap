#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <string.h>
#include "zmsg.h"
#include "zpts.h"
#include "zcrvw.h"
#include "bool.h"
#include "CUnit/Basic.h"

static ecpts_t *pts1;
static eccrvw_t *crv;

/*
 * Private functions
 */

void            test_msg2pts2msg(void);
// void test_pts2msg(void);

/*
 * Function
 */

/*
 * The suite initialization function.  * Opens the temporary file used by
 * the tests.  * Returns zero on success, non-zero otherwise.  
 */

int
zmsg_init_suite(void)
{
    mpz_t           p,
                    n,
                    a4,
                    a6,
                    r4,
                    r6,
                    gx,
                    gy,
                    r;

    /*
     * Init the curve
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

    mpz_clears(gx, gy, p, n, a4, a6, r4, r6, r, NULL);

    return 0;
}

/*
 * The suite cleanup function. Closes the temporary file used by the
 * tests. Returns zero on success, non-zero otherwise. 
 */
int
zmsg_clean_suite(void)
{
    /*
     * Destroy everything
     */

    pts1 = ecpts_destroy(pts1);
    // eccrvw_destroy(crv);

    return 0;
}

void
test_zmsg()
{
    CU_pSuite       pSuite = NULL;

    /*
     * add a suite to the registry 
     */
    pSuite =
        CU_add_suite("Test suite for zmsg module", zmsg_init_suite,
                     zmsg_clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        // return CU_get_error();
    }

    if (!CU_add_test(pSuite, "test of msg2pts2msg()", test_msg2pts2msg)) {
        CU_cleanup_registry();
        // return CU_get_error();
    }
}

void
test_msg2pts2msg()
{
    char            msg[] = "Hello World";
    char           *str1;

    str1 = NULL;
    pts1 = ecpts_init();

    CU_ASSERT(1 == msg2pts(pts1, msg, crv));

    str1 = pts2msg(pts1);

    CU_ASSERT(str1 != NULL);
    CU_ASSERT(strcmp(msg, str1) == 0);
}
