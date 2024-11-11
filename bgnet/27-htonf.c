#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

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

uint32_t htonf(float f)
{
    uint32_t i;
    uint32_t sign = 0;

    if (f < 0) {
        sign = 1;
        f = -f;
    }

    // i[31] = sign bit
    i = sign << 31;

    // i[30 to 16] = int(f)[14 to 0]
    i |= (((uint32_t) f) & 0x7fff) << 16;

    // i[15 to 0] = fraction(f) bits [15 to 0]
    i |= (uint32_t) ((f - (uint32_t) f) * 65536.0f) & 0xffff;

    return i;
}

float ntohf(uint32_t i)
{
    // integer part = i[14 to 0]
    float f = (i >> 16) & 0x7fff;

    // fraction part = i[15 to 0]
    f += (i & 0xffff) / 65536.0f;

    // sign = i[31]
    if ((i >> 31) & 1)
        f = -f;

    return f;
}

int main()
{
    uint32_t data;

    data = htonf(3.1415926);

    printf("%s\n", bin(data, sizeof data));
    printf("%ju\n", (uintmax_t) data);
    printf("%f\n", ntohf(data));

    return EXIT_SUCCESS;
}
