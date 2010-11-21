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
 * @file zap.c
 * @brief Implement a little command line utility that use libzap
 * @author <mayeu.tik@gmail.com> <pierrealain.toret@gmail.com>
 * @date 2010/10/19
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "zcrvw.h"
#include "zpts.h"
#include "zdh.h"
int
main(int argc, const char *argv[])
{
    /*
     * Pointer to the file used by the tests. 
     */
    FILE           *file = NULL;
    char            line[250];
    char           *pline = line;
    char           *kax = NULL,
        *kay = NULL,
        *kbx = NULL,
        *kby = NULL;
    int             line_number = 0;
    eccrvw_t       *crv;
    ecpts_t        *P,
                   *A,
                   *B,
                   *KA,
                   *KB;
    mpz_t           p,
                    n,
                    a4,
                    a6,
                    r4,
                    r6,
                    gx,
                    gy,
                    r,
                    a,
                    b;
    bool            res = false;
    /*
     * The suite initialization function. * Opens the temporary file used
     * by the tests. * Returns zero on success, non-zero otherwise. 
     */
    file = fopen("crv.txt", "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            pline = index(line, '=');
            switch (line_number) {
            case 1:
                mpz_init_set_str(p, ++pline, 10);
                break;
            case 2:
                mpz_init_set_str(n, ++pline, 10);
                break;
            case 3:
                mpz_init_set_str(a4, ++pline, 10);
                break;
            case 4:
                mpz_init_set_str(a6, ++pline, 10);
                break;
            case 5:
                mpz_init_set_str(r4, ++pline, 10);
                break;
            case 6:
                mpz_init_set_str(r6, ++pline, 10);
                break;
            case 7:
                mpz_init_set_str(gx, ++pline, 10);
                break;
            case 8:
                mpz_init_set_str(gy, ++pline, 10);
                break;
            case 9:
                mpz_init_set_str(r, ++pline, 10);
                break;
            }
        }
    }
    fclose(file);
    crv = eccrvw_create(p, n, a4, a6, r4, r6, gx, gy, r);
    P = ecpts_init_set(crv->gx, crv->gy, crv, false);
    kax = mpz_get_str(kax, 16, P->x);
    kay = mpz_get_str(kay, 16, P->y);
    printf("point P choisi : (%s,%s)\n", kax, kay);


    mpz_init(a);
    mpz_init(b);
    A = ecpts_init();
    B = ecpts_init();
    KA = ecpts_init();
    KB = ecpts_init();
    dh_first_step(A, a, P);
    kax = mpz_get_str(kax, 16, A->x);
    kay = mpz_get_str(kay, 16, A->y);
    printf("premier calcul de A : (%s,%s)\n", kax, kay);

    dh_first_step(B, b, P);
    kbx = mpz_get_str(kbx, 16, B->x);
    kby = mpz_get_str(kby, 16, B->y);
    printf("premier calcul de B : (%s,%s)\n", kbx, kby);

    dh_second_step(KA, a, B);
    kax = mpz_get_str(kax, 16, KA->x);
    kay = mpz_get_str(kay, 16, KA->y);
    printf("second calcul de A : (%s,%s)\n", kax, kay);


    dh_second_step(KB, b, A);
    kbx = mpz_get_str(kbx, 16, KB->x);
    kby = mpz_get_str(kby, 16, KB->y);
    printf("second calcul de B : (%s,%s)\n", kbx, kby);


    res = dh_check_keys(KA, KB);
    if (res == true)
        printf("WIN !\n");
    else
        printf("FAIL !\n");
    kax = mpz_get_str(kax, 16, KA->x);
    kbx = mpz_get_str(kbx, 16, KB->x);
    kay = mpz_get_str(kay, 16, KA->y);
    kby = mpz_get_str(kby, 16, KB->y);
    printf("clef de A : (%s,%s)\n", kax, kay);
    printf("clef de B : (%s,%s)\n", kbx, kby);
    ecpts_destroy(A);
    ecpts_destroy(B);
    ecpts_destroy(KA);
    ecpts_destroy(KB);
    return EXIT_SUCCESS;
}
