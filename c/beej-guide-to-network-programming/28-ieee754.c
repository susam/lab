#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define pack_float(f) (pack754((f), 32, 8))
#define unpack_float(f) (unpack754((f), 32, 8))
#define pack_double(f) (pack754((f), 64, 11))
#define unpack_double(f) (unpack754((f), 64, 11))

char *bin(uintmax_t n, size_t size)
{
    static char result[256];
    int i, j;

    j = 0;
    for (i = size * CHAR_BIT - 1; i >= 0; i--) {
        result[j++] = (n >> i) & 1 ? '1' : '0';
        if (i % CHAR_BIT == 0)
            result[j++] = ' ';
    }
    result[j] = '\0';
    return result;
}

uint64_t pack754(double f, unsigned bits, unsigned expbits)
{
    int bias = (1 << (expbits - 1)) - 1;
    int fracbits = bits - expbits - 1;
    int sign = 0;
    intmax_t exp = 0, frac;

    if (f == 0.0)
        return 0;

    if (f < 0) {
        sign = 1;
        f = -f;
    }

    while (f >= 2.0) {
        f /= 2.0;
        exp++;
    }

    while (f < 1.0) {
        f *= 2.0;
        exp--;
    }

    f -= 1.0;
    
    exp += bias;
    frac = f * (1ll << fracbits);

    // S E . . . . . . E C . . . . . . . . . . . . . . . . . . . . . C
    // 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
    // 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
    return (sign << (bits - 1)) | (exp << fracbits) | frac;
}

double unpack754(uint64_t i, unsigned bits, unsigned expbits)
{
    int bias = (1 << (expbits - 1)) - 1;
    int fracbits = bits - expbits - 1;
    intmax_t exp;
    double f;

    if (i == 0)
        return 0.0;

    f = (i & ~(~0ll << fracbits));
    f /= (1ll << fracbits);
    f += 1.0;

    exp = ((i >> fracbits) & ~(~0ll << expbits));
    exp -= bias;

    while (exp > 0) {
        f *= 2.0;
        exp--;
    }

    while (exp < 0) {
        f /= 2.0;
        exp++;
    }

    return f;
}

int main()
{
    double f;
    uint32_t i;
    uint64_t j;

    f = 3.14159265358979323;
    i = pack_float(f);
    printf("f: %.7f\n", f);
    printf("i: 0x%08jx - %s\n", (intmax_t) i, bin(i, 4));
    f = unpack_float(i);
    printf("f: %.7f\n\n", f);

    f = 3.14159265358979323;
    j = pack_double(f);
    printf("f: %.20f\n", f);
    printf("j: 0x%016jx - %s\n", (intmax_t) j, bin(j, 8));
    f = unpack_double(j);
    printf("f: %.20f\n\n", f);

    return EXIT_SUCCESS;
}
