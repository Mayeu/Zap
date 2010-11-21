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
    ecpts_t        *tmp,
                   *pt;

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
    // tmp = ecpts_init_set(Q->x, Q->y, Q->C, Q->inf);

    /*
     * Q is the additive inverse of P
     * We return the point at infinity
     */
    tmp = ecpts_init();
    zinvert(tmp, Q);

    if (ecpts_are_equals(P, tmp)) {
        ecpts_set_inf(R, true);
        ecpts_destroy(tmp);
        return;
    }

    ecpts_destroy(tmp);

    pt = ecpts_init();

    /*
     * P and Q are equals
     * We return the double of P
     */
    if (ecpts_are_equals(P, Q)) {
        zdouble(pt, P);
        ecpts_cpy(R, pt);
        ecpts_destroy(pt);      /* Free */
        return;
    }

    /*
     * addition
     */
    add_pts(pt, P, Q);
    ecpts_cpy(R, pt);

    ecpts_destroy(pt);
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
    ecpts_t        *pt;

    pt = ecpts_init();
    C = P->C;

    /*
     * xr
     */
    mpz_set(pt->x, P->x);

    /*
     * yr
     */
    mpz_ui_sub(pt->y, 0, P->y);
    mpz_mod(pt->y, pt->y, C->p);

    /*
     * Misc
     */
    ecpts_set_inf(pt, P->inf);
    ecpts_set_curve(pt, P->C);

    ecpts_cpy(R, pt);

    /*
     * Free the memory
     */
    ecpts_destroy(pt);

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
    ecpts_t        *pt;
    eccrvw_t       *C;

    pt = ecpts_init();
    C = P->C;

    /*
     * Lambda
     */
    mpz_inits(lmbd, lmbd2, tmp, NULL);

    mpz_mul(lmbd, P->x, P->x);  /* lmbd = xp^2 */
    mpz_mul_ui(lmbd, lmbd, 3);  /* lmbd = 3xp^2 */
    mpz_add(lmbd, lmbd, C->a4); /* lmbd = 3xp^2 + a4 */
    mpz_add(lmbd2, P->y, P->y); /* lmbd2 = 2yp */
    mpz_invert(lmbd2, lmbd2, C->p);     /* lmbd2 = 2yp^-1 */
    mpz_mul(lmbd, lmbd, lmbd2); /* lmbd = (3xp^2 + a4) / yp^2 */
    mpz_mod(lmbd, lmbd, C->p);

    /*
     * xr
     */
    mpz_mul(pt->x, lmbd, lmbd); /* xr = lmbd^2 */
    mpz_mul_ui(tmp, P->x, 2);   /* tmp = 2xp */
    mpz_sub(pt->x, pt->x, tmp); /* xr = lmbd^2 - 2xp */
    mpz_mod(pt->x, pt->x, C->p);        /* stay in the additive ring ! */

    /*
     * yr
     */
    mpz_neg(pt->y, lmbd);       /* yr = -lmbd */
    mpz_mul(pt->y, pt->y, pt->x);       /* yr = -lmbd*xr */
    mpz_mul(tmp, lmbd, P->x);   /* tmp = lmbd*xp */
    mpz_add(pt->y, pt->y, tmp); /* yr = -lmbd*xr + lmbd*xp */
    mpz_sub(pt->y, pt->y, P->y);        /* yr = -lmbd*xr + lmbd*xp - yp */
    mpz_mod(pt->y, pt->y, C->p);        /* stay in the additive ring ! */

    /*
     * Misc part
     */
    ecpts_set_inf(pt, P->inf);
    ecpts_set_curve(pt, P->C);

    /*
     * Copy the result in R
     */
    ecpts_cpy(R, pt);

    /*
     * Free the memory
     */
    mpz_clears(lmbd, lmbd2, tmp, NULL);
    ecpts_destroy(pt);

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
     * if k = 0, we return the point at infinity
     */
    if (mpz_cmp_ui(k, 0) == 0) {
        ecpts_set_inf(R, true);
        return;
    }

    /*
     * if P is the point at infinity, there is nothing to do 
     */
    if (ecpts_is_inf(P))
        return;

    nb = NULL;

    nb = mpz_get_str(nb, 2, k); /* we convert k into a string of bit */

    /*
     * we start at n-1 bit
     */
    while (*(++nb) != '\0') {
        zdouble(R, R);
        if (*nb == '1')
            zadd(R, R, P);
        }
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
    mpz_t           lmbd,
                    tmp;
    ecpts_t        *pt;
    eccrvw_t       *C;          /* the curve of the points */

    pt = ecpts_init();
    C = P->C;

    mpz_inits(lmbd, tmp, NULL);

    /*
     * lmbd
     */
    mpz_sub(lmbd, Q->y, P->y);  /* lmbd = yq - yp */
    mpz_sub(tmp, Q->x, P->x);   /* tmp = xq - xp */
    mpz_invert(tmp, tmp, C->p); /* tmp = (xq - xp)^-1 */
    mpz_mul(lmbd, lmbd, tmp);   /* lmbd = (yq - yp) / (xq - xp) */
    mpz_mod(lmbd, lmbd, C->p);  /* Stay in your division ring */

    /*
     * xr
     */
    mpz_mul(pt->x, lmbd, lmbd); /* xr = lmbd^2 */
    mpz_sub(pt->x, pt->x, P->x);        /* xr = lmbd^2 - xp */
    mpz_sub(pt->x, pt->x, Q->x);        /* xr = lmbd^2 - xp - xq */
    mpz_mod(pt->x, pt->x, C->p);        /* Stay in your division ring ! */

    /*
     * yr
     */
    mpz_neg(pt->y, lmbd);       /* yr = -lmbd */
    mpz_mul(pt->y, pt->y, pt->x);       /* yr = -lmbd * xr */
    mpz_mul(tmp, lmbd, P->x);   /* tmp = lmbd * xp */
    mpz_add(pt->y, pt->y, tmp); /* yr = -lmbd * xr + lmbd*xp */
    mpz_sub(pt->y, pt->y, P->y);        /* yr = -lmbd * xr + lmbd*xp - yp */
    mpz_mod(pt->y, pt->y, C->p);        /* Stay in your division ring ! */

    /*
     * Misc
     */
    ecpts_set_inf(pt, P->inf);
    ecpts_set_curve(pt, P->C);

    ecpts_cpy(R, pt);

    /*
     * Free the memory
     */
    mpz_clears(lmbd, tmp, NULL);
    ecpts_destroy(pt);

    return;
}
