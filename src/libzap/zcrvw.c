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

    crv = (eccrvw_t *) malloc(sizeof(eccrvw_t));        /* allocate the
                                                         * curve */
    eccrvw_set_all(crv, p, n, a4, a6, r4, r6, gx, gy, r);       /* set the 
                                                                 * coordinates */
    return crv;                 /* return the pointer to the curve */
}


/**
 * @brief Deallocate a curve
 * @param the curve
 * @return void
 */

eccrvw_t       *
eccrvw_destroy(eccrvw_t * crv)
{
    if (crv != NULL) {
        if (crv->p != NULL)
            mpz_clear(crv->p);
        if (crv->n != NULL)
            mpz_clear(crv->n);
        if (crv->a4 != NULL)
            mpz_clear(crv->a4);
        if (crv->a6 != NULL)
            mpz_clear(crv->a6);
        if (crv->r4 != NULL)
            mpz_clear(crv->r4);
        if (crv->r6 != NULL)
            mpz_clear(crv->r6);
        if (crv->gx != NULL)
            mpz_clear(crv->gx);
        if (crv->gy != NULL)
            mpz_clear(crv->gy);
        if (crv->r != NULL)
            mpz_clear(crv->r);

        /*
         * clean * the * parameters * of * the * curve 
         */

        free(crv);
    }
    return NULL;                /* free the memory */
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
    mpz_init_set(crv->p, p);
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
    mpz_init_set(crv->n, n);
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
    mpz_init_set(crv->a4, a4);
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
    mpz_init_set(crv->a6, a6);
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
    mpz_init_set(crv->r4, r4);
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
    mpz_init_set(crv->r6, r6);
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
    mpz_init_set(crv->gx, gx);
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
    mpz_init_set(crv->gy, gy);
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
    mpz_init_set(crv->r, r);
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

bool
eccrvw_are_equals(eccrvw_t * crv1, eccrvw_t * crv2)
{
    if (mpz_cmp(crv1->p, crv2->p) == 0)
        if (mpz_cmp(crv1->n, crv2->n) == 0)
            if (mpz_cmp(crv1->a4, crv2->a4) == 0)
                if (mpz_cmp(crv1->a6, crv2->a6) == 0)
                    if (mpz_cmp(crv1->r4, crv2->r4) == 0)
                        if (mpz_cmp(crv1->r6, crv2->r6) == 0)
                            if (mpz_cmp(crv1->gx, crv2->gx) == 0)
                                if (mpz_cmp(crv1->gy, crv2->gy) == 0)
                                    if (mpz_cmp(crv1->r, crv2->r) == 0)
                                        return true;

    return false;
}
