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
 * @file zmsg.c
 * @brief function to translate point to message and message to point
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/14
 */

/**
 * Includes
 */
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include "zcrvw.h"
#include "zpts.h"
#include "zmsg.h"

/*
 * Define
 */

/*
 * Functions
 */

/*
 * @brief Translate a char message to point
 *
 * Translate a message to a point. For simplicity reason,  this version can not
 * transform a message that need to be chunked. The binary version of the
 * message has to be lesser than p.
 * This function take a string that represente the message and return the
 * associated point simply by calculating the y coordinate from the binary
 * version of the message.
 *
 * @param pts, the point that will receive the message
 * @param msg, the string to translate to point
 * @param crv, the curve used
 * @return 1 if everything goes well, 0 either
 */

int
msg2pts(ecpts_t * pts, char *msg, eccrvw_t * crv)
{
    mpz_t           msg_z,
                    tmp,
                    p;

    mpz_init_set_ui(msg_z, 0);

    /*
     * Converting the char to a mpz
     */
    while (*msg != '\0') {
        mpz_mul_ui(msg_z, msg_z, 256);  /* Shift 1 octet to the left */
        mpz_add_ui(msg_z, msg_z, (int) *msg);
        msg++;
    }

    /*
     * Test if the msg is lesser than the P value of the curve
     */
    if (mpz_cmp(crv->p, msg_z) <= 0)
        return 0;               /* message to big */

    /*
     * The size is ok, we calculate the y coordinate of the point
     */
    ecpts_set_x(pts, msg_z);
    ecpts_set_curve(pts, crv);
    ecpts_set_inf(pts, false);

    mpz_inits(tmp, p, NULL);
    mpz_pow_ui(pts->y, pts->x, 3);      /* y = x^3 */
    mpz_mul(tmp, pts->x, crv->a4);      /* tmp = a4*x */
    mpz_add(pts->y, pts->y, tmp);       /* y = x^3 + a4*x */
    mpz_add(pts->y, pts->y, crv->a6);   /* y = x^3 + a4*x + a6 */
    mpz_mod(pts->y, pts->y, crv->p);    /* Stay in your additive ring ! */
    mpz_sub_ui(p, crv->p, 1);
    mpz_divexact_ui(p, p, 2);
    mpz_powm(pts->y, pts->y, p, crv->p);        /* y^2 = x^3 + a4*x + a6 */

    return 1;
}

/*
 * @brief Translate a point to a message
 *
 * @param pts, the point to translate
 * @return the string that represent the message
 */

char           *
pts2msg(ecpts_t * pts)
{
    char           *msg,
                   *tmp,
                   *msg_hex;
    int             shift;

    msg = (char *) calloc(sizeof(char), 33);    /* allocate a 512 bits
                                                 * size * * long string +
                                                 * null char */
    msg_hex = NULL;
    tmp = msg;

    /*
     * get the msg in hexa
     */
    msg_hex = mpz_get_str(msg_hex, 16, pts->x);

    shift = 1;
    while (*msg_hex != '\0') {
        *msg =
            *msg | ((*msg_hex > 'A') ? (*msg_hex - 'A' + 10)
                    : (*msg_hex - '0'));
        if (shift)
            *msg = (*msg) << 4;
        else
            msg++;

        shift = (shift + 1) % 2;
        msg_hex++;
    }

    *msg = '\0';

    return tmp;
}
