#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};

int sieve_bound(int num)
{
    double dnum, dres;
    if (num <= 20)
        return 100;
    dnum = num;
    dres = dnum * (log(dnum) + log(log(dnum)));
    return (int) round(dres);
}

void fill_sieve(struct sieve_t *s);
int  is_prime(struct sieve_t *sv, unsigned n);

int nth_prime(struct sieve_t *s, int N)
{
    int cnt, p;
    if (N == 1)
        return 2;
    if (N == 2)
        return 3;

    cnt = 2;
    p = 5;

    for (; ; ) {
        if (is_prime(s, p)) {
            cnt += 1;
            if (cnt == N)
                break;
        }
        p += 2;
        if (is_prime(s, p)) {
            cnt += 1;
            if (cnt == N)
                break;
        }
        p += 4;
    }

    return p;
}

int main()
{
    int n, outp;
    int res;
    struct sieve_t *s;

    res = scanf("%d", &n);
    assert(res == 1);
    s = (struct sieve_t *) malloc(sizeof(struct sieve_t));
    s->n = ((sieve_bound(n) / CHAR_BIT) / 6) + 1;
    s->mod1 = (unsigned char *) calloc(s->n, sizeof(char));
    s->mod5 = (unsigned char *) calloc(s->n, sizeof(char));

    fill_sieve(s);

#if 0
    {
        int i = 0, k = 0;
        printf("primes:\n");
        while (k < n) {
            if (is_prime(s, i)) {
                printf("%d ", i);
                k += 1;
            }
            i += 1;
        }
        printf("\n");
    }
#endif

    outp = nth_prime(s, n);
    printf("%d\n", outp);

    free(s->mod1);
    free(s->mod5);
    free(s);
}

#line 10000







int is_prime(struct sieve_t *sv, unsigned n) {
    unsigned int   var = 0;
    unsigned int   rmndr = 0;
    unsigned int   byte_ind = 0;
    unsigned int   bit_ind  = 0;
    unsigned char* array_ptr = 0;
    unsigned int   upper_bound = sv->n * 8;

    assert(sv != NULL);

    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;

    rmndr = n % 6;
    if (rmndr == 0 || rmndr == 2 ||
        rmndr == 3 || rmndr == 4) return 0;

    var = (n - rmndr) / 6;

    if (var >= upper_bound) return 0;

    byte_ind = var / 8;
    bit_ind  = var % 8;

    if (rmndr == 1) {
        array_ptr = sv->mod1;
    } else array_ptr = sv->mod5;

    if (((array_ptr[byte_ind] >> bit_ind) & 1) == 0) {
        return 1;
    } else return 0;

    return 0;
}

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
