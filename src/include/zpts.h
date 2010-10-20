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
 * @file zpts.h
 * @brief Define the points structure and functions to manipulate it
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/13
 */

#ifndef __ZPTS_H
#define __ZPTS_H

/*
 * Include
 */

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <errno.h>
#include "zcrvw.h"

/*
 * Define
 */

/*
 * Struct
 */

/**
 * @struct ecpts
 * @brief A point of an elliptic curve
 *
 * This structure represent a point of an elliptic curve. This point is
 * determine by two coordinate that are define on Z
 */
typedef struct _ECPTS {
    mpz_t           x;          /* !< x coordinate */
    mpz_t           y;          /* !< y coordinate */
    eccrvw_t       *C;          /* !< the curve associated to this point */
} ecpts_t;

/*
 * Functions
 */

/**
 * @brief Allocate and initialize a point
 * @param the x value
 * @param the y value
 * @param the curve structure
 * @return a pointer to an ecpts_t or NULL if there was an error
 */

ecpts_t        *ecpts_create(mpz_t x, mpz_t y, eccrvw_t * C);

/**
 * @brief Copy a point in an other
 * @param the destination point
 * @param the source point
 * @result
 */

void            ecpts_cpy(ecpts_t * D, ecpts_t * S);

/**
 * @brief Deallocate a point
 * @param the point
 * @return void
 */

void            ecpts_destroy(ecpts_t * pts);

/**
 * @brief set the value of x
 * @param the point
 * @param the value of x
 * @return void
 */

void            ecpts_set_x(ecpts_t * pts, mpz_t x);

/**
 * @brief set the value of y
 * @param the point
 * @param the value of y
 * @return void
 */

void            ecpts_set_y(ecpts_t * pts, mpz_t y);

/**
 * @brief set the curve of the point
 * @param the point
 * @param the curve
 * @return EINVAL if C is NULL, EXIT_SUCCESS either
 */

int             ecpts_set_curve(ecpts_t * pts, eccrvw_t * C);

/**
 * @brief set both x and y
 * @param the point
 * @param the value of x
 * @param the value of y
 * @param the curve
 * @return EINVAL if C is NULL,EXIT_SUCCESS either
 */

int             ecpts_set_all(ecpts_t * pts, mpz_t x, mpz_t y,
                              eccrvw_t * C);

#endif                          /* __ZPTS_H */
