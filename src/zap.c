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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "bool.h"
#include "zcrvw.h"
#include "zpts.h"
#include "zdh.h"

void
dh_protocol(char *fname, bool verbose)
{

    FILE           *file = NULL;
    char            line[250];
    char           *pline = line;
    char           *kax = NULL,
        *kay = NULL,
        *kbx = NULL,
        *kby = NULL,
        *ra = NULL,
        *rb = NULL;
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
    // Opening of the curve file and assigning values to the curve
    // variable
    srand(time(NULL));
    file = fopen(fname, "r");
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
        fclose(file);           // Closing the file
        /*
         * Creation of the curve according to what has been read in the
         * description file
         */
        crv = eccrvw_create(p, n, a4, a6, r4, r6, gx, gy, r);
        P = ecpts_init_set(crv->gx, crv->gy, crv, false);
        if (verbose == true) {
            kax = mpz_get_str(kax, 16, P->x);
            kay = mpz_get_str(kay, 16, P->y);
            printf("P   : (%s,\n       %s)\n\n", kax, kay);
        }
        /*
         * A and B are computing their own values KA and KB according to P and 
         * the 2 random numbers computed a and b
         */
        mpz_init(a);
        mpz_init(b);
        A = ecpts_init();
        B = ecpts_init();
        KA = ecpts_init();
        KB = ecpts_init();
        dh_first_step(A, a, P);
        if (verbose == true) {
            kax = mpz_get_str(kax, 16, A->x);
            kay = mpz_get_str(kay, 16, A->y);
            ra = mpz_get_str(ra, 16, a);
            printf("r A : (%s)\n", ra);
            printf("1 A : (%s,\n       %s)\n\n", kax, kay);
        }
        dh_first_step(B, b, P);
        if (verbose == true) {
            kbx = mpz_get_str(kbx, 16, B->x);
            kby = mpz_get_str(kby, 16, B->y);
            rb = mpz_get_str(rb, 16, b);
            printf("r B : (%s)\n", rb);
            printf("1 B : (%s,\n       %s)\n\n", kbx, kby);
        }
        /*
         * A and B exchange the values computed previously and compute the 
         * new ones
         */
        dh_second_step(KA, a, B);
        if (verbose == true) {
            kax = mpz_get_str(kax, 16, KA->x);
            kay = mpz_get_str(kay, 16, KA->y);
            printf("2 A : (%s,\n       %s)\n", kax, kay);
        }
        dh_second_step(KB, b, A);
        if (verbose == true) {
            kbx = mpz_get_str(kbx, 16, KB->x);
            kby = mpz_get_str(kby, 16, KB->y);
            printf("2 B : (%s,\n       %s)\n\n", kbx, kby);
        }
        // Now we check if the 2 final keys computed on both sides are the
        // same
        res = dh_check_keys(KA, KB);
        if (res == true) {
            kax = mpz_get_str(kax, 16, KA->x);
            kay = mpz_get_str(kay, 16, KA->y);
            printf("key : (%s,\n       %s)\n", kax, kay);

        } else if (verbose == true) {
            printf("FAIL !\n\n");
        }
        ecpts_destroy(A);
        ecpts_destroy(B);
        ecpts_destroy(KA);
        ecpts_destroy(KB);
        eccrvw_destroy(crv);
    }
    return;
}

int
main(int argc, char *argv[])
{
    bool            vflag = false;
    bool            start_dh = false,
        start_mm = false;
    char           *mvalue = NULL;
    char           *cvalue = NULL;
    int             index;
    int             c;

    opterr = 0;

    while ((c = getopt(argc, argv, "vm:c:")) != -1)
        switch (c) {
        case 'v':
            vflag = true;
            break;
        case 'm':
            mvalue = optarg;
            start_mm = true;
            break;
        case 'c':
            cvalue = optarg;
            start_dh = true;
            break;
        case '?':
            if (optopt == 'c')
                fprintf(stderr,
                        "Option -%c requires a elliptic curve file as an argument.\n",
                        optopt);
            else if (optopt == 'm')
                fprintf(stderr,
                        "Option -%c requires a message to encrypt as an argument\n",
                        optopt);
            else if (isprint(optopt)) {
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            } else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n", optopt);
            fprintf(stderr, "Usages of zap\n");
            fprintf(stderr,
                    "zap -d [-v] \"path-to-weierstrass-elliptic-curve\"\n");
            fprintf(stderr, "zap -m [-v] \"message-to-encrypt\"\n\n");
            fprintf(stderr,
                    "argument -d indicates the Diffie-Hellman protocol\n");
            fprintf(stderr,
                    "         -m indicates the use of the Massey-Omura encryption\n");
            fprintf(stderr, "option -v for verbose output\n");
            return EXIT_FAILURE;
        default:
            return EXIT_FAILURE;
        }

    /*
     * printf ("dflag = %d, mvalue = %s, cvalue = %s\n", vflag, mvalue,
     * cvalue); 
     */

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    if (start_dh == true)
        dh_protocol(cvalue, vflag);
    else if (start_mm == true); // mm_encrypt(mvalue, vflag);

    else {                      // If we don't have to do anything the
        // call to Zap is bad
        fprintf(stderr, "Usages of zap\n");
        fprintf(stderr,
                "zap -d [-v] \"path-to-weierstrass-elliptic-curve\"\n");
        fprintf(stderr, "zap -m [-v] \"message-to-encrypt\"\n\n");
        fprintf(stderr,
                "argument -d indicates the Diffie-Hellman protocol\n");
        fprintf(stderr,
                "         -m indicates the use of the Massey-Omura encryption\n");
        fprintf(stderr, "option -v for verbose output\n");
    }
    return EXIT_SUCCESS;
}
