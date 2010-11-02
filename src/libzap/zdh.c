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

/*
 * Includes
 */

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <bool.h>
#include "zdh.h"

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

void
dh_rand_gen(mpz_t p, int size)
{
    gmp_randstate_t state;      /* random init stat */
    unsigned long   i;

    i = 0;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    do {
        mpz_urandomb(p, state, size);
    } while (!isprime(p));

    /*
     * Free Ressources
     */
    gmp_randclear(state);
}

/*
 * @brief run the Diffie-Hellman protocol and return the key
 * @param the curve we use
 * @param the point we give to compute the key
 * @return the key
 */

ecpts * dh(eccrvw_t * crv, ecpts_t * P) {
	
	mpz_t a, b;
	(ecpts_t *) A, B, kA, kB;
	
	mpz_init(a);
	mpz_init(b);
	//rand_a and rand_b are initialized so we can compute 2 random numbers.
	
	dh_rand_gen(a, crv->); //determine if the order of the group is p or n
	dh_rand_gen(b, crv->);
	
	//Alice and Bob compute their own part of the key
	zmult(A, P, a);
	zmult(B, P, b);
	
	//Alice and Bob will compute the same key after all
	zmult(kA, B, a);
	zmult(kB, A, b);
	
	return kA;
}