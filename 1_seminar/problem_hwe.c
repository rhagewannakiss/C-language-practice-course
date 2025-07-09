#include "u_template.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void fill_sieve(struct sieve_t *sv) {
    unsigned int upper_bound = 6*(sv->n*8 - 1) + 5;
    unsigned int p1 = 0;
    unsigned int p5 = 0;
    unsigned int byte_ind_i = 0;
    unsigned int bit_ind_i  = 0;
    unsigned int byte_ind1 = 0;
    unsigned int bit_ind1  = 0;
    unsigned int ind1 = 0;
    unsigned int byte_ind5 = 0;
    unsigned int bit_ind5  = 0;
    unsigned int ind5 = 0;
    unsigned int var = 0;
    unsigned int rmndr = 0;
    unsigned int i = 0;

    assert(sv != NULL);
    sv->mod1[0] |= 1;

    for (; p1 * p1 <= upper_bound; i++) {
        p1 = 6*i + 1;
        p5 = p1 + 4;
        byte_ind_i = i / 8;
        bit_ind_i = i % 8;

        if (((sv->mod1[byte_ind_i] >> bit_ind_i) & 1) == 0) {
            var = p1 * p1;
            while (var <= upper_bound) {
                rmndr = var % 6;
                ind1  = (var - rmndr) / 6;
                byte_ind1 = ind1 / 8;
                bit_ind1 = ind1 % 8;
                if (rmndr == 1) {
                    sv->mod1[byte_ind1] |= 1 << bit_ind1;
                } else if (rmndr == 5) {
                    sv->mod5[byte_ind1] |= 1 << bit_ind1;
                } var += 2 * p1;
            }
        }

        if (((sv->mod5[byte_ind_i] >> bit_ind_i) & 1) == 0) {
            var = p5 * p5;
            while (var <= upper_bound) {
                rmndr = var % 6;
                ind5 = (var - rmndr) / 6;
                byte_ind5 = ind5 / 8;
                bit_ind5 = ind5 % 8;
                if (rmndr == 1) {
                    sv->mod1[byte_ind5] |= 1 << bit_ind5;
                }
                else if (rmndr == 5) {
                    sv->mod5[byte_ind5] |= 1 << bit_ind5;
                }
                var += 2 * p5;
            }
        }
    }
}
