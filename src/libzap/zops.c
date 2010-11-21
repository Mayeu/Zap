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
 * Private functions declaration
 */

void            add_pts(ecpts_t * R, ecpts_t * P, ecpts_t * Q);

/*
 * Functions
 */

/*
 * @brief Addition of two points of the curve
 * @param the result point
 * @param the first point to add
 * @param the second point to add
 * @result void
 */

void
zadd(ecpts_t * R, ecpts_t * P, ecpts_t * Q)
{
    ecpts_t        *tmp;

    /*
     * P is the point at infinity
     * We return Q
     */
    if (ecpts_is_inf(P)) {
        ecpts_cpy(R, Q);
        return;
    }

    /*
     * Q is the point at infinity
     * We return P
     */
    if (ecpts_is_inf(Q)) {
        ecpts_cpy(R, P);
        return;
    }

    /*
     * We create the point tmp. We arbitrary initiate it with the Q value (to
     * avoid losing time with other initialisation
     */
    tmp = ecpts_init_set(Q->x, Q->y, Q->C, Q->inf);

    /*
     * Q is the additive inverse of P
     * We return the point at infinity
     */
    zinvert(tmp, Q);

    if (ecpts_are_equals(P, tmp)) {
        ecpts_set_inf(R, true);
        return;
    }

    /*
     * P and Q are equals
     * We return the double of P
     */
    if (ecpts_are_equals(P, Q)) {
        zdouble(R, P);
        return;
    }

    /*
     * addition
     */
    add_pts(R, P, Q);

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

    /*
     * xr
     */
    mpz_set(R->x, P->x);

    /*
     * yr
     */
    mpz_add(R->y, P->x, P->y);
    mpz_mod(R->y, R->y, C->p);

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
    mpz_t           lmbd,
                    lmbd2,
                    tmp;
    eccrvw_t       *C;

    C = P->C;

    /*
     * Lambda
     */
    mpz_inits(lmbd, lmbd2, tmp);
    mpz_mul(lmbd, P->x, P->x);  /* lmbd = xp^2 */
    mpz_mul_ui(lmbd, lmbd, 3);  /* lmbd = 3xp^2 */
    // mpz_mul(tmp, P->x, C->a2); /* tmp = a2*xp */
    // mpz_mul_ui(tmp, tmp, 2); /* tmp = 2a2*xp */
    // mpz_add(lmbd, lmbd, tmp); /* lmbd = 3xp^2 + 2a2*xp */
    mpz_add(lmbd, lmbd, C->a4); /* lmbd = 3xp^2 + 2a2*xp + a4 */
    // mpz_mul(tmp, C->a1, P->y); /* tmp = a1*py */
    // mpz_sub(lmbd, lmbd, tmp); /* lmbd = 3xp^2 + 2a2*xp + a4 - a1*py */
    mpz_add(lmbd2, P->y, P->y); /* lmbd2 = 2yp */
    // mpz_mul(tmp, C->a1, P->x); /* tmp = a1*xp */
    // mpz_add(lmbd2, lmbd2, tmp); /* lmbd2 = yp^2 + a1*xp */
    // mpz_add(lmbd2, lmbd2, C->a3); /* lmbd2 = yp^2 + a1*yp + a3 */
    mpz_invert(lmbd2, lmbd2, C->p);     /* lmbd2 = lmbd2^-1 */
    mpz_mul(lmbd, lmbd, lmbd2); /* lmbd = (3xp^2 + 2a2*xp + a4 - a1*py) /
                                 * (yp^2 + a1*yp + a3) */
    mpz_mod(lmbd, lmbd, C->p);

    /*
     * xr
     */
    mpz_mul(R->x, lmbd, lmbd);  /* xr = lmbd^2 */
    // mpz_mul(tmp, lmbd, C->a1); /* tmp = a1*lmbd */
    // mpz_add(R->x, R->x, tmp); /* xr = lmbd^2 + a1*lmbd */
    // mpz_sub(R->x, R->x, a2); /* xr = lmbd^2 + a1*lmbd - a2 */
    mpz_sub(R->x, R->x, P->x);  /* xr = lmbd^2 + a1*lmbd - a2 - xp */
    mpz_mod(R->x, R->x, C->p);  /* stay in the additive ring ! */

    /*
     * yr
     */
    // mpz_add(R->y, lmbd, C->a1); /* yr = lmbd + a1 */
    mpz_mul_si(R->y, lmbd, -1); /* yr = -(lmbd + a1) */
    mpz_mul(R->y, R->y, R->x);  /* yr = -(lmbd + a1)xr */
    mpz_mul(tmp, lmbd, P->x);   /* tmp = lmbd*xp */
    mpz_add(R->y, R->y, tmp);   /* yr = -(lmbd + a1)xr + lmbd*xp */
    mpz_sub(R->y, R->y, P->y);  /* yr = -(lmbd + a1)xr + lmbd*xp - yp */
    // mpz_sub(R->y, R->y, C->a3); /* yr = -(lmbd + a1)xr + lmbd*xp - yp - 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // a3 */
    mpz_mod(R->y, R->y, C->p);  /* stay in the additive ring ! */

    mpz_clears(lmbd, lmbd2, tmp);

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
     * if P is the point at infinity, there is nothing to do 
     */
    if (ecpts_is_inf(P))
        return;

    /*
     * we start at n-1 bit
     */
    nb++;
    while (*nb != '\0') {       // modif by pat
        zadd(R, R, R);
        if (*nb == '1') {
            zadd(R, R, P);
        }
        nb++;
    }
    return;
}

/*
 * Private Functions
 */

/*
 * @brief Addition of two different points of the curve
 * @param the result point
 * @param the first point to add
 * @param the second point to add
 * @result void
 */

void
add_pts(ecpts_t * R, ecpts_t * P, ecpts_t * Q)
{
    mpz_t           X,
                    lmbd,
                    tmp;
    eccrvw_t       *C;          /* the curve of the points */

    C = P->C;

    mpz_inits(X, lmbd, tmp);

    /*
     * X
     */
    mpz_add(X, P->x, Q->x);     /* X = xp + xq */

    /*
     * lmbd
     */
    mpz_add(lmbd, P->y, Q->y);  /* lmbd = yp + yq */
    mpz_invert(tmp, X, C->p);   /* tmp = X^-1 */
    mpz_mul(lmbd, lmbd, X);     /* lmbd = (yp + yq) * X^-1 */

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
