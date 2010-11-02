#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "zops.h"
#include "zcrvw.h"
#include "bool.h"
#include "CUnit/Basic.h"

static eccrvw_t *crv;
/*
 * The different parameters of the curve 
 */
static mpz_t    p,
                n,
                a4,
                a6,
                r4,
                r6,
                gx,
                gy,
                r;

mpz_init_set(p,
             "8884933102832021670310856601112383279507496491807071433260928721853918699951");
mpz_init_set(n,
             "8884933102832021670310856601112383279454437918059397120004264665392731659049");
mpz_init_set(a4,
             "2481513316835306518496091950488867366805208929993787063131352719741796616329");
mpz_init_set(a6,
             "4387305958586347890529260320831286139799795892409507048422786783411496715073");
mpz_init_set(r4,
             "5473953786136330929505372885864126123958065998198197694258492204115618878079");
mpz_init_set(r6,
             "5831273952509092555776116225688691072512584265972424782073602066621365105518");
mpz_init_set(gx,
             "7638166354848741333090176068286311479365713946232310129943505521094105356372");
mpz_init_set(gy,
             "762687367051975977761089912701686274060655281117983501949286086861823169994");
mpz_init_set(r,
             "8094458595770206542003150089514239385761983350496862878239630488323200271273");

/*
 * Simple test of eccrvw_create(). Check that the curve is correctly
 * allocated and that the value are the expected ones. Must be run as the 
 * first test. 
 */
void
test_eccrvw_create(void)
{
    if (NULL != (crv = eccrvw_create(p, n, a4, a6, r4, r6, gx, gy, r))) {
        CU_ASSERT(p == crv->p);
        CU_ASSERT(n == crv->n);
        CU_ASSERT(a4 == crv->a4);
        CU_ASSERT(a6 == crv->a6);
        CU_ASSERT(r4 == crv->r4);
        CU_ASSERT(r6 == crv->r6);
        CU_ASSERT(gx == crv->gx);
        CU_ASSERT(gy == crv->gy);
        CU_ASSERT(r == crv->r);
    }
}

/*
 * Simple test of eccrvw_destroy(). 
 * Check that the curve is correctly destroyed.
 */
void
test_eccrvw_destroy(void)
{
    eccrvw_destroy(crv);
    CU_ASSERT(NULL == crv);
}

/*
 * Simple test of eccrvw_are_equals().
 * Test the comparison of 2 curves.
 */

void
test_eccrvw_are_equals(void)
{

    CU_ASSERT(true == eccrvw_are_equals(crv, crv));

    mpz_t           p_temp,
                    n_temp,
                    a4_temp,
                    a6_temp,
                    r4_temp,
                    r6_temp,
                    gx_temp,
                    gy_temp,
                    r_temp;
    eccrvw_t       *crv_temp;

    mpz_init_set(p_temp,
                 "69428135827422558556814728087082390245228647644190881373725431623333703313183");
    mpz_init_set(n_temp,
                 "69428135827422558556814728087082390245536059518300429952449622908895954150897");
    mpz_init_set(a4_temp,
                 "24570906224682738350877904676272618945451424201156704579955527687857931907116");
    mpz_init_set(a6_temp,
                 "26641199534355228319204959392053020430911508233543587067096305334304620831215");
    mpz_init_set(r4_temp,
                 "13859800071163587486198631864159067850303413260768897292752501936206767783966");
    mpz_init_set(r6_temp,
                 "40311589282612276948382455933284548131862963620708401055908592468074901010960");
    mpz_init_set(gx_temp,
                 "29514627309339036373561965441490845980268442328419547059948011994060902660237");
    mpz_init_set(gy_temp,
                 "22516619028672274076547206220594027997420705225198403837573285248008219117181");
    mpz_init_set(r_temp,
                 "36878232356269389776306787699640758499619962068010091712712453025807263336800");

    crv_temp =
        eccrvw_create(p_temp, n_temp, a4_temp, a6_temp, r4_temp, r6_temp,
                      gx_temp, gy_temp, r_temp);
    CU_ASSERT(false == eccrvw_are_equals(crv, crv_temp));

}
