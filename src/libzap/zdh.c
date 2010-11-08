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
#include <time.h>

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

    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_urandomb(p, state, size);

    /*
     * Free Ressources
     */
    gmp_randclear(state);
}

/*
 * @brief run the Diffie-Hellman protocol and return the key
 * @param the curve we use
 * @param the point we give to compute the key
 * @return the key or the infinity point as an error value
 */

ecpts_t        *
dh(eccrvw_t * crv, ecpts_t * P)
{

    mpz_t           a;
    mpz_t          *pa = &a;
    mpz_t           b;
    mpz_t          *pb = &b;
    bool            ret = false;
    ecpts_t        *A;
    ecpts_t        *B;
    ecpts_t        *kA;
    ecpts_t        *kB;

    mpz_init(a);
    mpz_init(b);
    // rand_a and rand_b are initialized so we can compute 2 random
    // numbers.

    dh_rand_gen(pa, mpz_get_ui(crv->p));        // determine if the order
                                                // of the group is
    // p or n
    dh_rand_gen(pb, crv->p);

    // Alice and Bob compute their own part of the key
    zmult(A, P, pa);
    zmult(B, P, pb);

    // Alice and Bob will compute the same key after all
    zmult(kA, B, a);
    zmult(kB, A, b);

    if (ecpts_are_equals(kA, kB) == true)
        ret = true;

    if (ret == true)
        return kA;
    else {
        ecpts_set_inf(kA, true);
        return kA;
    }
}