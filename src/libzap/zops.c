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

void            zadd(ecpts_t * R, ecpts_t * P, ecpts_t * Q)
{
   mpz_t  X ;

   mpz_init (X) ;

   mpz_add(X, P->x, Q->x) ;
}

/*
 * @brief Calculate the additive inverse of a point of the curve
 * @param the result point
 * @param the point to invert
 * @result void
 */

void            zinvert(ecpts_t * R, ecpts_t * P, ecpts_t * Q)
{}

/*
 * @brief Calculate the double of a point
 * @param the result point
 * @param the point to double
 * @result void
 */

void            zdouble(ecpts_t * R, ecpts_t * P)
{}

/*
 * @brief Calculate the multiplication between a point and a scalar
 * @param the result point
 * @param the point
 * @param the scalar
 * @result
 */

void            zmult(ecpts_t * R, ecpts_t * P, mpz_t x)
{}

