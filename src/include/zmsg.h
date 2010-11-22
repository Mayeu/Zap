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
 * @file zmsg.h
 * @brief Define functions to translate point to message and message to point
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/14
 */

#ifndef __ZMSG_H
#define __ZMSG_H

/*
 * Include
 */

#include <gmp.h>
#include "bool.h"
#include "zcrvw.h"
#include "zpts.h"

/*
 * Define
 */

/*
 * Struct
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

int             msg2pts(ecpts_t * pts, char *msg, eccrvw_t * crv);

/*
 * @brief Translate a point to a message
 *
 * @param pts, the point to translate
 * @return the string that represent the message
 */

char           *pts2msg(ecpts_t * pts);

#endif                          /* __ZMSG_H */
