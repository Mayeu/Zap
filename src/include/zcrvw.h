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
 * @file zcrvw.h
 * @brief Define the points structure and functions to manipulate it
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/14
 */

#ifndef __ZCRVW_H
#define __ZCRVW_H

/*
 * Include
 */

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <bool.h>

/*
 * Define
 */

/*
 * Struct
 */

/**
 * @struct eccrvw
 * @brief An elliptic curve
 *
 * This structure represent an elliptic curve according to the files
 * provided by the Arcana-ECDB. Some parameters are given plus the 
 * the coordinates of a point G belonging to the curve.
 * A curve is such that y^2 = x^3 + a4 ∗ x + a6
 */
typedef struct _ECCRVW {
    mpz_t           p;
    mpz_t           n;          /* !< the number of Fp-rational points of
                                 * the curve */
    mpz_t           a4;
    mpz_t           a6;
    mpz_t           r4;
    mpz_t           r6;
    mpz_t           gx;         /* !< x coordinate of the g point of the
                                 * curve */
    mpz_t           gy;         /* !< y coordinate of the g point of the
                                 * curve */
    mpz_t           r;
} eccrvw_t;
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

eccrvw_t       *eccrvw_create(mpz_t p, mpz_t n, mpz_t a4, mpz_t a6,
                              mpz_t r4, mpz_t r6, mpz_t gx, mpz_t gy,
                              mpz_t r);

/**
 * @brief Deallocate a curve
 * @param the curve
 * @return void
 */

void            eccrvw_destroy(eccrvw_t * crv);


/**
 * @brief return the value of p, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the p value
 */

void            eccrvw_get_p(mpz_t p, eccrvw_t * crv);

/**
 * @brief return the value of n, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the n value
 */

void            eccrvw_get_n(mpz_t n, eccrvw_t * crv);

/**
 * @brief return the value of a4, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the a4 value
 */

void            eccrvw_get_a4(mpz_t a4, eccrvw_t * crv);

/**
 * @brief return the value of a6, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the a6 value
 */

void            eccrvw_get_a6(mpz_t a6, eccrvw_t * crv);

/**
 * @brief return the value of r4, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the r4 value
 */

void            eccrvw_get_r4(mpz_t r4, eccrvw_t * crv);

/**
 * @brief return the value of r6, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the r6 value
 */

void            eccrvw_get_r6(mpz_t r6, eccrvw_t * crv);

/**
 * @brief return the value of gx, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the gx value
 */

void            eccrvw_get_gx(mpz_t gx, eccrvw_t * crv);

/**
 * @brief return the value of gy, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the gy value
 */

void            eccrvw_get_gy(mpz_t gy, eccrvw_t * crv);

/**
 * @brief return the value of r, the returned value is safe to modify
 * @param the elliptic curve 
 * @return a pointer to the r value
 */

void            eccrvw_get_r(mpz_t r, eccrvw_t * crv);


/**
 * @brief set the value of p
 * @param the elliptic curve
 * @param the value of p
 * @return void
 */

void            eccrvw_set_p(eccrvw_t * crv, mpz_t p);

/**
 * @brief set the value of n
 * @param the elliptic curve
 * @param the value of n
 * @return void
 */

void            eccrvw_set_n(eccrvw_t * crv, mpz_t n);

/**
 * @brief set the value of a4
 * @param the elliptic curve
 * @param the value of a4
 * @return void
 */

void            eccrvw_set_a4(eccrvw_t * crv, mpz_t a4);

/**
 * @brief set the value of a6
 * @param the elliptic curve
 * @param the value of a6
 * @return void
 */

void            eccrvw_set_a6(eccrvw_t * crv, mpz_t a6);

/**
 * @brief set the value of r4
 * @param the elliptic curve
 * @param the value of r4
 * @return void
 */

void            eccrvw_set_r4(eccrvw_t * crv, mpz_t r4);

/**
 * @brief set the value of r6
 * @param the elliptic curve
 * @param the value of r6
 * @return void
 */

void            eccrvw_set_r6(eccrvw_t * crv, mpz_t r6);

/**
 * @brief set the value of gx
 * @param the elliptic curve
 * @param the value of gx
 * @return void
 */

void            eccrvw_set_gx(eccrvw_t * crv, mpz_t gx);

/**
 * @brief set the value of gy
 * @param the elliptic curve
 * @param the value of gy
 * @return void
 */

void            eccrvw_set_gy(eccrvw_t * crv, mpz_t gy);

/**
 * @brief set the value of r
 * @param the elliptic curve
 * @param the value of r
 * @return void
 */

void            eccrvw_set_r(eccrvw_t * crv, mpz_t r);

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

void            eccrvw_set_all(eccrvw_t * crv, mpz_t p, mpz_t n,
                               mpz_t a4, mpz_t a6, mpz_t r4,
                               mpz_t r6, mpz_t gx, mpz_t gy, mpz_t r);

/**
 * @brief determines if the 2 curves are equal
 * @param the elliptic curve
 * @param the second elliptic curve
 * @return true if they're equal 
 *         false otherwise
 */

bool eccrvw_are_equals(eccrvw_t * crv1, eccrvw_t * crv2);

#endif                          /* __ZCRVW_H */
