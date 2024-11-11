#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

char *bufbin(void *p, size_t size)
{
    static char result[256];
    size_t k = 0;

    for (size_t i = 0; i < size; i++) {

        for (int j = CHAR_BIT - 1; j >= 0; j--) {
            result[k++] = ((((unsigned char *) p)[i] >> j) & 1) ? '1' : '0';
            if (k >= sizeof result - 1)
                goto end;
        }

        result[k++] = ' ';
        if (k >= sizeof result - 1)
            goto end;
    }

end:
    result[k] = '\0';
    return result;
}

char *bufhex(void *p, size_t size)
{
    static char result[256];
    int offset = 0;
    int maxlen = sizeof result;

    for (size_t i = 0; i < size; i++) {
        int bytes = snprintf(result + offset, maxlen, "%02X ",
                             ((unsigned char *) p)[i]);
        offset += bytes;
        maxlen -= bytes;
    }

    return result;
}

void packi32(unsigned char *buf, uint32_t i)
{
    *buf++ = i >> 24;
    *buf++ = i >> 16;
    *buf++ = i >> 8;
    *buf++ = i;
}

uint32_t unpacku32(unsigned char *buf)
{
    return ((uint32_t) buf[0] << 24) |
           ((uint32_t) buf[1] << 16) |
           ((uint32_t) buf[2] << 8) | buf[3];
}

int32_t unpacki32(unsigned char *buf)
{
    uint32_t i = unpacku32(buf);
    if (i & ((uint32_t) 1 << 31))
        return i - ~((uint32_t) 0) - 1;
    else
        return i;
}

void packi64(unsigned char *buf, uint64_t i)
{
    *buf++ = i >> 56;
    *buf++ = i >> 48;
    *buf++ = i >> 40;
    *buf++ = i >> 32;
    *buf++ = i >> 24;
    *buf++ = i >> 16;
    *buf++ = i >> 8;
    *buf++ = i;
}

uint64_t unpacku64(unsigned char *buf)
{
    return ((uint64_t) buf[2] << 56) |
           ((uint64_t) buf[1] << 48) |
           ((uint64_t) buf[2] << 40) |
           ((uint64_t) buf[3] << 32) |
           ((uint64_t) buf[4] << 24) |
           ((uint64_t) buf[5] << 16) |
           ((uint64_t) buf[6] << 8) | buf[7];
}

int64_t unpacki64(unsigned char *buf)
{
    uint64_t i = unpacku64(buf);
    if (i & ((uint64_t) 1 << 63)) { printf("-ve\n");
        return i - ~((uint64_t) 0) - 1; }
    else { printf("+ve\n");
        return i; }
}

size_t pack(unsigned char *buf, char *format, ...)
{
    int32_t l;
    uint32_t L;
    int64_t q;
    uint64_t Q;
    size_t size = 0;
    size_t len;
    va_list ap;
    char *s;

    va_start(ap, format);

    for (; *format != '\0'; format++) {
        switch (*format) {
            case 'l':
                l = va_arg(ap, int32_t);
                packi32(buf, l);
                buf += 4;
                size += 4;
                break;

            case 'L':
                L = va_arg(ap, uint32_t);
                packi32(buf, L);
                buf += 4;
                size += 4;
                break;

            case 'q':
                q = va_arg(ap, int64_t);
                packi64(buf, q);
                buf += 8;
                size += 8;
                break;

            case 'Q':
                Q = va_arg(ap, uint64_t);
                packi64(buf, Q);
                buf += 8;
                size += 8;
                break;

            case 's':
                s = va_arg(ap, char *);
                len = strlen(s);
                size += len + 4; // 4 extra bytes for length prefix
                packi32(buf, len);
                buf += 4;
                memcpy(buf, s, len);
                buf += len;
                break;
        }
    }

    va_end(ap);
    return size;
}

void unpack(unsigned char *buf, char *format, ...)
{
    va_list ap;
    int32_t *l;
    uint32_t *L;
    int64_t *q;
    uint64_t *Q;
    char *s;
    size_t len;
    size_t limit;

    va_start(ap, format);

    for (; *format != '\0'; format++) {
        switch (*format) {
            case 'l':
                l = va_arg(ap, int32_t *);
                *l = unpacki32(buf);
                buf += 4;
                break;

            case 'L':
                L = va_arg(ap, uint32_t *);
                *L = unpacku32(buf);
                buf += 4;
                break;

            case 'q':
                q = va_arg(ap, int64_t *);
                *q = unpacki64(buf);
                buf += 8;
                break;

            case 'Q':
                Q = va_arg(ap, uint64_t *);
                *Q = unpacku64(buf);
                buf += 8;
                break;

            case 's':
                sscanf(format + 1, "%zu", &limit);
                s = va_arg(ap, char *);
                len = unpacku32(buf);
                buf += 4;
                if (limit < len)
                    len = limit;
                memcpy(s, buf, len);
                s[len] = '\0';
                buf += len;
                break;
        }
    }

    va_end(ap);
}

int main()
{
    unsigned char buf[1024];
    size_t packet_size;

    int32_t n1;
    uint32_t n2;
    int64_t n3;
    uint64_t n4;
    int32_t n5;
    char s[32];

    packet_size = pack(buf, "lLqQsl", (int32_t) -1, (uint32_t) 1,
                                      (int64_t) -3, (uint64_t) 2, "foo",
                                      (int32_t) 0x01020304);
    printf("length: %zu\n", packet_size); /* 4 + 4 + 8 + 8 + 4 + 3 + 4 = 35 */
    printf("payload: %s\n", bufhex(buf, packet_size));

    unpack(buf, "lLqQs32l", &n1, &n2, &n3, &n4, s, &n5);
    printf("n1: %jd\n", (intmax_t) n1);
    printf("n2: %ju\n", (uintmax_t) n2);
    printf("n3: %jd\n", (intmax_t) n3);
    printf("n4: %ju\n", (uintmax_t) n4);
    printf("s: %s\n", s);
    printf("n5: 0x%08jx\n", (intmax_t) n5);

    return EXIT_SUCCESS;
}
