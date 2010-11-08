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
dh_rand_gen(mpz_t p, mpz_t size)
{
    gmp_randstate_t state;      /* random init stat */

    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    mpz_urandomm(p, state, size);

    /*
     * Free Ressources
     */
    gmp_randclear(state);
}
/*
 * @brief generate a random number
 * @param an allocated pointer, and a initialized mpz
 * @param the maximal size of the generated number
 */

void            dh_rand_gen(mpz_t p, mpz_t size);

/*
 * @brief compute one's internal part of the key
 * @param an allocated pointer, and a initialized mpz
 * @param a pointer to the chosen point of the curve
 */

ecpts_t        *
dh_first_step(mpz_t s, ecpts_t *P)
{
    ecpts_t        *S;
    // Computation of the radom number
    dh_rand_gen(s, P->C->p);
    // Computation of one's part of the key
    zmult(S, P, s);
    return S;
}

/*
 * @brief compute one's external part of the key
 * @param an allocated pointer, and a initialized mpz
 * @param a pointer to the internal part of the key
 */

ecpts_t        *
dh_second_step(mpz_t s, ecpts_t *P)
{
    ecpts_t        *K;
    // Computation of the foreign part of the key
    zmult(K, P, s);
    return K;
}

/*
 * @brief check if the 2 keys are the same
 * @param a pointer to the first key
 * @param a pointer to the second key
 */

bool
dh_check_keys(ecpts_t* KA, ecpts_t* KB)
{
    if (ecpts_are_equals(KA, KB) == true)
        return true;
    else
        return false;
}
