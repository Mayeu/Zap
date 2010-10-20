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
 * @file zops.c
 * @brief Implement functions to add, double, inverse, and multiplication of a point
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/13
 */

/*
 * Include
 */

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "zpts.h"
#include "zops.h"

/*
 * Define
 */

/*
 * Functions
 */

/*
 * @brief Addition two point of the curve
 * @param the result point
 * @param the first point to add
 * @param the second point to add
 * @result void
 */

void
zadd(ecpts_t * R, ecpts_t * P, ecpts_t * Q)
{
    mpz_t           X,
                    lmbd;
    eccrvw_t       *C;          /* the curve of the points */

    C = P->C;

    mpz_inits(X, lmbd);

    /*
     * X
     */
    mpz_add(X, P->x, Q->x);     /* X = xp + xq */

    /*
     * lmbd
     */
    mpz_add(lmbd, P->y, Q->y);  /* lmbd = yp + yq */
    mpz_divexact(lmbd, lmbd, X);        /* lmbd = (yp + yq) / X */

    /*
     * xr
     */
    mpz_mul(R->x, lmbd, lmbd);  /* xr = lmbd^2 */
    mpz_add(R->x, R->x, lmbd);  /* xr = lmbd^2 + lmbd */
    mpz_add(R->x, R->x, X);     /* xr = lmbd^2 + lmbd + X */
    mpz_mod(R->x, R->x, C->p);  /* Stay in your division ring ! */

    /*
     * yr
     */
    mpz_add_ui(R->y, lmbd, 1);  /* yr = (lmbd + 1) */
    mpz_mul(R->y, R->y, R->x);  /* yr = (lmbd + 1) * xr */
    mpz_mul(lmbd, lmbd, P->x);  /* lmbd = lmbd * xp ; we can * use lmbd to 
                                 * temp the value * since it will not be
                                 * reuse. */
    mpz_add(R->y, R->y, lmbd);  /* yr = (lmbd + 1) * xr + * lmbd*xp */
    mpz_add(R->y, R->y, P->y);  /* yr = (lmbd + 1) * xr + lmbd*xp + yp */
    mpz_mod(R->y, R->y, C->p);  /* Stay in your division ring ! */

    return;
}

/*
 * @brief Calculate the additive inverse of a point of the curve
 * @param the result point
 * @param the point to invert
 * @result void
 */

void
zinvert(ecpts_t * R, ecpts_t * P)
{
    eccrvw_t       *C;

    C = P->C;

    mpz_set(R->x, P->x);
    mpz_add(R->x, P->x, P->y);
    mpz_mod(R->x, R->x, C->p);

    return;
}

/*
 * @brief Calculate the double of a point
 * @param the result point
 * @param the point to double
 * @result void
 */

void
zdouble(ecpts_t * R, ecpts_t * P)
{
    mpz_t           lmbd;
    eccrvw_t       *C;

    C = P->C;

    /*
     * Lambda
     */
    mpz_divexact(lmbd, P->y, P->x);     /* lmbd = yp/xp */
    mpz_add(lmbd, lmbd, P->x);  /* lmbd = xp + yp/xy */

    /*
     * xr
     */
    mpz_mul(R->x, lmbd, lmbd);  /* xr = lmbd^2 */
    mpz_add(R->x, R->x, lmbd);  /* xr = lmbd^2 + lmbd */
    mpz_mod(R->x, R->x, C->p);

    /*
     * yr
     */
    mpz_mul(R->y, P->x, P->x);  /* yr = xp^2 */
    mpz_mul(lmbd, lmbd, R->x);  /* lmbd = lmbd * xr */
    mpz_add(R->y, R->y, lmbd);  /* yr = xp^2 + lmbd * xr */
    mpz_add(R->y, R->y, R->x);  /* yr = xp^2 + lmbd * xr + xr */
    mpz_mod(R->x, R->x, C->p);

    return;
}

/*
 * @brief Calculate the multiplication between a point and a scalar
 * @param the result point
 * @param the point
 * @param the scalar
 * @result
 */

void
zmult(ecpts_t * R, ecpts_t * P, mpz_t k)
{
    char           *nb;

    nb = NULL;

    nb = mpz_get_str(nb, 2, k); /* we convert k into a string of bit */

    ecpts_cpy(R, P);

    /*
     * we start at n-1 bit
     */
    while (++nb != NULL) {
    }

}
