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
 * @file test_zpts.c
 * @brief Test the zpts module
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
#include "bool.h"
#include "zcrvw.h"
#include "zpts.h"
#include "zops.h"

/*
 * Global point for the tests
 */
static ecpts_t *pts1,
               *pts2;
// *pts3;

static eccrvw_t *crv;

/*
 * Private functions
 */
void            test_zinvert();
void            test_zdouble();
void            test_zadd();
void            test_zmult();

/*
 * Function
 */

/*
 * The suite initialization function.  * Opens the temporary file used by
 * the tests.  * Returns zero on success, non-zero otherwise.  
 */
int
zops_init_suite(void)
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

    mpz_clears(p, n, a4, a6, r4, r6, r, NULL);

    /*
     * Init the point
     */

    pts1 = ecpts_init_set(gx, gy, crv, false);
    pts2 = ecpts_init();

    mpz_clears(gx, gy, NULL);

    return 0;
}

/*
 * The suite cleanup function. Closes the temporary file used by the
 * tests. Returns zero on success, non-zero otherwise. 
 */
int
zops_clean_suite(void)
{
    /*
     * Destroy everything
     */

    pts1 = ecpts_destroy(pts1);
    pts2 = ecpts_destroy(pts2);
    // eccrvw_destroy(crv);

    return 0;
}

void
test_zops()
{
    CU_pSuite       pSuite = NULL;

    /*
     * add a suite to the registry 
     */
    pSuite =
        CU_add_suite("Test suite for zops module", zops_init_suite,
                     zops_clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        // return CU_get_error();
    }


    if ((!CU_add_test(pSuite, "test of zinvert()", test_zinvert))
        || (!CU_add_test(pSuite, "test of zdouble()", test_zdouble))
        || (!CU_add_test(pSuite, "test of zadd()", test_zadd))
        || (!CU_add_test(pSuite, "test of zmult()", test_zmult))) {
        CU_cleanup_registry();
        // return CU_get_error();
    }
}

/*
 * Private Functions
 */

void
test_zinvert()
{

    mpz_t           x,
                    y;
    ecpts_t        *pts1_invert;

    mpz_init_set_str(x,
                     "7638166354848741333090176068286311479365713946232310129943505521094105356372",
                     10);
    mpz_init_set_str(y,
                     "8122245735780045692549766688410697005446841210689087931311642634992095529957",
                     10);
    pts1_invert = ecpts_init_set(x, y, crv, false);

    zinvert(pts2, pts1);

    CU_ASSERT(true == ecpts_are_equals(pts2, pts1_invert));

    /*
     * Free the memory
     */
    ecpts_destroy(pts1_invert);
    mpz_clears(x, y, NULL);

    return;
}

void
test_zdouble()
{

    mpz_t           x,
                    y;
    ecpts_t        *pts1_double;

    mpz_init_set_str(x,
                     "863754428068677557929687025502332508399472799151289953149508604923086976251",
                     10);
    mpz_init_set_str(y,
                     "2263694661988027868788176657560100371119172698625506618490887528730945004028",
                     10);
    pts1_double = ecpts_init_set(x, y, crv, false);

    zdouble(pts2, pts1);

    CU_ASSERT(true == ecpts_are_equals(pts2, pts1_double));

    /*
     * Free the memory !
     */
    ecpts_destroy(pts1_double);
    mpz_clears(x, y, NULL);

    return;
}

void
test_zadd()
{
    mpz_t           x,
                    y;
    ecpts_t        *pts_inf,
                   *pts1_double,
                   *pts_add,
                   *pts1_inverse;

    /*
     * add to the point to infinity
     */
    pts_inf = ecpts_init();
    ecpts_set_inf(pts_inf, true);

    zadd(pts2, pts_inf, pts1);

    CU_ASSERT(true == ecpts_are_equals(pts2, pts1));

    zadd(pts2, pts1, pts_inf);

    CU_ASSERT(true == ecpts_are_equals(pts2, pts1));

    /*
     * inverse
     */

    mpz_init_set_str(x,
                     "7638166354848741333090176068286311479365713946232310129943505521094105356372",
                     10);
    mpz_init_set_str(y,
                     "8122245735780045692549766688410697005446841210689087931311642634992095529957",
                     10);
    pts1_inverse = ecpts_init_set(x, y, crv, false);

    zadd(pts2, pts1, pts1_inverse);

    CU_ASSERT(true == ecpts_is_inf(pts2));

    /*
     * double
     */
    mpz_init_set_str(x,
                     "863754428068677557929687025502332508399472799151289953149508604923086976251",
                     10);
    mpz_init_set_str(y,
                     "2263694661988027868788176657560100371119172698625506618490887528730945004028",
                     10);
    pts1_double = ecpts_init_set(x, y, crv, false);
    zadd(pts2, pts1, pts1);
    CU_ASSERT(true == ecpts_are_equals(pts2, pts1_double));
    /*
     * Two different point
     */
    mpz_init_set_str(x,
                     "800469382577851882430764267503379551369032669306397380363294188843884499915",
                     10);
    mpz_init_set_str(y,
                     "8735734427290128121604527478505598824582703967829400306565714269709266167368",
                     10);
    pts_add = ecpts_init_set(x, y, pts1->C, false);
    zadd(pts2, pts1, pts1_double);
    CU_ASSERT(true == ecpts_are_equals(pts2, pts_add));
    /*
     * Free the memory
     */
    mpz_clears(x, y, NULL);
    ecpts_destroy(pts1_double);
    ecpts_destroy(pts_add);
    ecpts_destroy(pts_inf);
    return;
}

void
test_zmult()
{
    return;
}
