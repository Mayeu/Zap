#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "zops.h"
#include "zcrvw.h"
#include "bool.h"
#include "CUnit/Basic.h"


void            test_eccrvw_init(void);
void            test_eccrvw_destroy(void);
void            test_eccrvw_are_equals(void);

static eccrvw_t *crv;
static mpz_t    p,
                n,
                a4,
                a6,
                r4,
                r6,
                gx,
                gy,
                r;

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
    /*
     * Destroy everything
     */

    return 0;
}

void
test_zcrvw()
{
    CU_pSuite       pSuite = NULL;

    /*
     * add a suite to the registry 
     */
    pSuite =
        CU_add_suite("Test suite for zcrvw module", init_suite1,
                     clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        // return CU_get_error();
    }


    if ((!CU_add_test(pSuite, "test_eccrvw_init()", test_eccrvw_init))
        ||
        (!CU_add_test
         (pSuite, "test of eccrvw_destroy()", test_eccrvw_destroy))
        ||
        (!CU_add_test
         (pSuite, "test_eccrvw_are_equals()", test_eccrvw_are_equals))
        ) {
        CU_cleanup_registry();
        // return CU_get_error();
    }

}

/*
 * Simple test of eccrvw_create(). Check that the curve is correctly
 * allocated and that the value are the expected ones. Must be run as the 
 * first test. 
 */
void
test_eccrvw_init(void)
{
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

    if (NULL != crv) {
        CU_ASSERT(0 == mpz_cmp(p, crv->p));
        CU_ASSERT(0 == mpz_cmp(n, crv->n));
        CU_ASSERT(0 == mpz_cmp(a4, crv->a4));
        CU_ASSERT(0 == mpz_cmp(a6, crv->a6));
        CU_ASSERT(0 == mpz_cmp(r4, crv->r4));
        CU_ASSERT(0 == mpz_cmp(r6, crv->r6));
        CU_ASSERT(0 == mpz_cmp(gx, crv->gx));
        CU_ASSERT(0 == mpz_cmp(gy, crv->gy));
        CU_ASSERT(0 == mpz_cmp(r, crv->r));
    }

}

/*
 * Simple test of eccrvw_destroy(). 
 * Check that the curve is correctly destroyed.
 */
void
test_eccrvw_destroy(void)
{
    crv = eccrvw_destroy(crv);
    CU_ASSERT(NULL == crv);
}

/*
 * Simple test of eccrvw_are_equals().
 * Test the comparison of 2 curves.
 */

void
test_eccrvw_are_equals(void)
{


    mpz_t           p_temp,
                    n_temp,
                    a4_temp,
                    a6_temp,
                    r4_temp,
                    r6_temp,
                    gx_temp,
                    gy_temp,
                    r_temp;
    eccrvw_t       *crv1,
                   *crv2;

    mpz_init_set_str(p_temp,
                     "69428135827422558556814728087082390245228647644190881373725431623333703313183",
                     10);
    mpz_init_set_str(n_temp,
                     "69428135827422558556814728087082390245536059518300429952449622908895954150897",
                     10);
    mpz_init_set_str(a4_temp,
                     "24570906224682738350877904676272618945451424201156704579955527687857931907116",
                     10);
    mpz_init_set_str(a6_temp,
                     "26641199534355228319204959392053020430911508233543587067096305334304620831215",
                     10);
    mpz_init_set_str(r4_temp,
                     "13859800071163587486198631864159067850303413260768897292752501936206767783966",
                     10);
    mpz_init_set_str(r6_temp,
                     "40311589282612276948382455933284548131862963620708401055908592468074901010960",
                     10);
    mpz_init_set_str(gx_temp,
                     "29514627309339036373561965441490845980268442328419547059948011994060902660237",
                     10);
    mpz_init_set_str(gy_temp,
                     "22516619028672274076547206220594027997420705225198403837573285248008219117181",
                     10);
    mpz_init_set_str(r_temp,
                     "36878232356269389776306787699640758499619962068010091712712453025807263336800",
                     10);

    crv1 =
        eccrvw_create(p_temp, n_temp, a4_temp, a6_temp, r4_temp, r6_temp,
                      gx_temp, gy_temp, r_temp);
    crv2 =
        eccrvw_create(p_temp, n_temp, a4_temp, a6_temp, r4_temp, r6_temp,
                      gx_temp, gy_temp, r_temp);
    CU_ASSERT(true == eccrvw_are_equals(crv1, crv1));
    CU_ASSERT(true == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_p(crv1, p);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_n(crv1, n);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_a4(crv1, a4);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_a6(crv1, a6);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_r4(crv1, r4);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_r6(crv1, r6);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_gx(crv1, gx);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_gy(crv1, gy);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));
    eccrvw_set_r(crv1, r);
    CU_ASSERT(false == eccrvw_are_equals(crv1, crv2));

    crv1 = eccrvw_destroy(crv1);
    crv2 = eccrvw_destroy(crv2);

}
