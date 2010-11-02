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
 * @file zcrvw.c
 * @brief Implemente functions to manipulate elliptic curves
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/14
 */

/**
 * Includes
 */
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "zcrvw.h"

/*
 * Define
 */

/*
 * Functions
 */

/**
 * @brief Allocate and initialize an elliptic curve
 * @param the p value
 * @param the n value
 * @param the a4 value
 * @param the a6 value
 * @param the r4 value
 * @param the r6 value
 * @param the gx value
 * @param the gy value
 * @param the r value
 * @return a pointer to an eccrvw_t or NULL if there was an error
 */

eccrvw_t
    * eccrvw_create(mpz_t p, mpz_t n, mpz_t a4, mpz_t a6,
                    mpz_t r4, mpz_t r6, mpz_t gx, mpz_t gy, mpz_t r)
{
    eccrvw_t       *crv;

    crv = (eccrvw_t *) malloc(sizeof(eccrvw_t));
    mpz_init_set(crv->p, p);
    mpz_init_set(crv->n, n);
    mpz_init_set(crv->a4, a4);
    mpz_init_set(crv->a6, a6);
    mpz_init_set(crv->r4, r4);
    mpz_init_set(crv->r6, r6);
    mpz_init_set(crv->gx, gy);
    mpz_init_set(crv->gy, gy);
    mpz_init_set(crv->r, r);

    return crv;
}


/**
 * @brief Deallocate a curve
 * @param the curve
 * @return void
 */

void
eccrvw_destroy(eccrvw_t * crv)
{
    mpz_clears(crv->p, crv->n, crv->a4, crv->a6, crv->r4, crv->r6, crv->gx,
               crv->gy, crv->r);

    free(crv);
}


/**
 * @brief return the value of p, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the p value
 */

void
eccrvw_get_p(mpz_t p, eccrvw_t * crv)
{
    mpz_set(p, crv->p);
}

/**
 * @brief return the value of n, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the n value
 */

void
eccrvw_get_n(mpz_t n, eccrvw_t * crv)
{
    mpz_set(n, crv->n);
}

/**
 * @brief return the value of a4, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the a4 value
 */

void
eccrvw_get_a4(mpz_t a4, eccrvw_t * crv)
{
    mpz_set(a4, crv->a4);
}

/**
 * @brief return the value of a6, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the a6 value
 */

void
eccrvw_get_a6(mpz_t a6, eccrvw_t * crv)
{
    mpz_set(a6, crv->a6);
}

/**
 * @brief return the value of r4, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the r4 value
 */

void
eccrvw_get_r4(mpz_t r4, eccrvw_t * crv)
{
    mpz_set(r4, crv->r4);
}

/**
 * @brief return the value of r6, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the r6 value
 */

void
eccrvw_get_r6(mpz_t r6, eccrvw_t * crv)
{
    mpz_set(r6, crv->r6);
}

/**
 * @brief return the value of gx, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the gx value
 */

void
eccrvw_get_gx(mpz_t gx, eccrvw_t * crv)
{
    mpz_set(gx, crv->gx);
}

/**
 * @brief return the value of gy, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the gy value
 */

void
eccrvw_get_gy(mpz_t gy, eccrvw_t * crv)
{
    mpz_set(gy, crv->gy);
}

/**
 * @brief return the value of r, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the r value
 */

void
eccrvw_get_r(mpz_t r, eccrvw_t * crv)
{
    mpz_set(r, crv->r);
}


/**
 * @brief set the value of p
 * @param the elliptic curve
 * @param the value of p
 * @return void
 */

void
eccrvw_set_p(eccrvw_t * crv, mpz_t p)
{
    mpz_set(crv->p, p);
}

/**
 * @brief set the value of n
 * @param the elliptic curve
 * @param the value of n
 * @return void
 */

void
eccrvw_set_n(eccrvw_t * crv, mpz_t n)
{
    mpz_set(crv->n, n);
}

/**
 * @brief set the value of a4
 * @param the elliptic curve
 * @param the value of a4
 * @return void
 */

void
eccrvw_set_a4(eccrvw_t * crv, mpz_t a4)
{
    mpz_set(crv->a4, a4);
}

/**
 * @brief set the value of a6
 * @param the elliptic curve
 * @param the value of a6
 * @return void
 */

void
eccrvw_set_a6(eccrvw_t * crv, mpz_t a6)
{
    mpz_set(crv->a6, a6);
}

/**
 * @brief set the value of r4
 * @param the elliptic curve
 * @param the value of r4
 * @return void
 */

void
eccrvw_set_r4(eccrvw_t * crv, mpz_t r4)
{
    mpz_set(crv->r4, r4);
}

/**
 * @brief set the value of r6
 * @param the elliptic curve
 * @param the value of r6
 * @return void
 */

void
eccrvw_set_r6(eccrvw_t * crv, mpz_t r6)
{
    mpz_set(crv->r6, r6);
}

/**
 * @brief set the value of gx
 * @param the elliptic curve
 * @param the value of gx
 * @return void
 */

void
eccrvw_set_gx(eccrvw_t * crv, mpz_t gx)
{
    mpz_set(crv->gx, gx);
}

/**
 * @brief set the value of gy
 * @param the elliptic curve
 * @param the value of gy
 * @return void
 */

void
eccrvw_set_gy(eccrvw_t * crv, mpz_t gy)
{
    mpz_set(crv->gy, gy);
}

/**
 * @brief set the value of r
 * @param the elliptic curve
 * @param the value of r
 * @return void
 */

void
eccrvw_set_r(eccrvw_t * crv, mpz_t r)
{
    mpz_set(crv->r, r);
}

/**
 * @brief set all parameters
 * @param the elliptic curve
 * @param the elliptic curve
 * @param the p value
 * @param the n value
 * @param the a4 value
 * @param the a6 value
 * @param the r4 value
 * @param the r6 value
 * @param the gx value
 * @param the gy value
 * @param the r value
 * @return void
 */

void
eccrvw_set_all(eccrvw_t * crv, mpz_t p, mpz_t n,
               mpz_t a4, mpz_t a6, mpz_t r4,
               mpz_t r6, mpz_t gx, mpz_t gy, mpz_t r)
{
    eccrvw_set_p(crv, p);
    eccrvw_set_n(crv, n);
    eccrvw_set_a4(crv, a4);
    eccrvw_set_a6(crv, a6);
    eccrvw_set_r4(crv, r4);
    eccrvw_set_r6(crv, r6);
    eccrvw_set_gx(crv, gx);
    eccrvw_set_gy(crv, gy);
    eccrvw_set_r(crv, r);
}

/**
 * @brief determines if the 2 curves are equal
 * @param the elliptic curve
 * @param the second elliptic curve
 * @return true if they're equal 
 *         false otherwise
 */

bool eccrvw_are_equals(eccrvw_t * crv1, eccrvw_t * crv2)
{
if (mpz_cmp(crv1->p, crv2->p) == 0)
        if (mpz_cmp(crv1->n, crv2->n) == 0)
        	if (mpz_cmp(crv1->a4, crv2->a6) == 0)
        		if (mpz_cmp(crv1->a6, crv2->a6) == 0)
        			if (mpz_cmp(crv1->r4, crv2->r4) == 0)
					if (mpz_cmp(crv1->r6, crv2->r6) == 0)
						if (mpz_cmp(crv1->gx, crv2->gx) == 0)
							if (mpz_cmp(crv1->gy, crv2->gy) == 0)
								if (mpz_cmp(crv1->r, crv2->r) == 0)

									return true;


    return false;

}

