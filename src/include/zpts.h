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
typedef struct _ECPTS
{
   mpz_t x ; /*!< x coordinate */
   mpz_t y ; /*!< y coordinate */
} ecpts_t

/*
 * Functions
 */

/**
 * @brief Allocate and initialize a point
 * @param the x value
 * @param the y value
 * @return a pointer to an ecpts_t or NULL if there was an error
 */

*ecpts_t ecpts_create (mpz_t x, mpz_t y) ;

/**
 * @brief return the value of x, the returned value is safe to modify
 * @param the points
 * @return a pointer to the x value
 */

*mpz_t ecpts_get_x (*ecpts_t pts) ;

/**
 * @brief return the value of y, the returned value is safe to modify
 * @param the points
 * @return a pointer to the y value
 */

*mpz_t ecpts_get_y (*ecpts_t pts) ;

/**
 * @brief set the value of x
 * @param the points
 * @param the value of x
 * @return void
 */

void ecpts_set_x (*ecpts_t pts, mpz_t x) ;

/**
 * @brief set the value of y
 * @param the points
 * @param the value of y
 * @return void
 */

void ecpts_set_x (*ecpts_t pts, mpz_t y) ;

/**
 * @brief set the both x and y
 * @param the points
 * @param the value of x
 * @param the value of y
 * @return void
 */

void ecpts_set_x (*ecpts_t pts, mpz_t x,  mpz_t y) ;

#endif /* __ZPTS_H */

