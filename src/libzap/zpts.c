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
 * @file zpts.c
 * @brief Implemente functions to manipulate points
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

/*
 * Define
 */

/*
 * Functions
 */

/**
 * @brief Allocate and initialize a point
 * @param the x value
 * @param the y value
 * @return a pointer to an ecpts_t or NULL if there was an error
 */

ecpts_t        *
ecpts_create(mpz_t x, mpz_t y, eccrvw_t * C)
{
    ecpts_t        *pts;

    pts = (ecpts_t *) malloc(sizeof(ecpts_t));  /* alloc the point */
    mpz_init(pts->x);           /* initialize the x coordinate */
    mpz_init(pts->y);           /* initialize the y coordinate */

    if (ecpts_set_all(pts, x, y, C) != EXIT_SUCCESS)
        return NULL;            /* if the set fail, for exemple, in case C 
                                 * is NULL */

    return pts;                 /* returne the pointer */
}

/**
 * @brief Copy a point in an other
 * @param the destination point
 * @param the source point
 * @result
 */

void ecpts_cpy(ecpts_t * D, ecpts_t * S) 
{
   mpz_set (R->x, P->x) ;
   mpz_set (R->y, P->y) ;
   R->C = P->C ;
}

/**
 * @brief Deallocate a point
 * @param the point
 * @return void
 */

void
ecpts_destroy(ecpts_t * pts)
{
    mpz_clears(pts->x, pts->y); /* clean the coordinate */

    eccrvw_destroy(pts->C);
    pts->C = NULL;

    free(pts);                  /* free the memory */
}

/**
 * @brief set the value of x
 * @param the point
 * @param the value of x
 * @return void
 */

void
ecpts_set_x(ecpts_t * pts, mpz_t x)
{
    mpz_set(pts->x, x);
}

/**
 * @brief set the value of y
 * @param the point
 * @param the value of y
 * @return void
 */

void
ecpts_set_y(ecpts_t * pts, mpz_t y)
{
    mpz_set(pts->y, y);
}

/**
 * @brief set the curve of the point
 * @param the point
 * @param the curve
 * @return EINVAL if C is NULL,EXIT_SUCCESS either
 */

int
ecpts_set_curve(ecpts_t * pts, eccrvw_t * C)
{
    if (C == NULL)
        return EINVAL;

    pts->C = C;

    return EXIT_SUCCESS;
}

/**
 * @brief set both x and y
 * @param the point
 * @param the value of x
 * @param the value of y
 * @param the curve
 * @return EINVAL if C is NULL,EXIT_SUCCESS either
 */

int
ecpts_set_all(ecpts_t * pts, mpz_t x, mpz_t y, eccrvw_t * C)
{
    ecpts_set_x(pts, x);
    ecpts_set_y(pts, y);

    return ecpts_set_curve(pts, C);
}
