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
 * @file dh.h
 * @brief Define the functions of the Diffie-Hellman key exchange
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/14
 */

#ifndef __DH_H
#define __DH_H

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
 * Functions
 */

/*
 * @brief generate a random number
 * @param an allocated pointer, and a initialized mpz
 * @param the maximal size of the generated number
 */

void            dh_rand_gen(mpz_t p, int size);

/*
 * @brief run the Diffie-Hellman protocol and return the key
 * @param the curve we use
 * @param the point we give to compute the key
 * @return the key or the infinity point as an error value
 */

ecpts          *dh(eccrvw_t * crv, ecpts_t * P);


#endif                          /* __DH_H */
