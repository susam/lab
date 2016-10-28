#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in sa;
    struct sockaddr_in6 sa6;
    int ret;
    char ipv4[INET_ADDRSTRLEN];
    char ipv6[INET6_ADDRSTRLEN];

    /* IPv4 */
    ret = inet_pton(AF_INET, "10.0.0.1", &sa.sin_addr);
    if (ret != 1) {
        fprintf(stderr, "Error %d\n", ret);
        return EXIT_FAILURE;
    }
    printf("IPv4: sa.sin_addr.s_addr: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", (sa.sin_addr.s_addr >> (i * 8)) & 0xff);
    }
    printf("\n");
    inet_ntop(AF_INET, &sa.sin_addr, ipv4, sizeof ipv4 / sizeof *ipv4);
    printf("IPv4: inet_ntop(): sa.sin_addr: %s\n", ipv4);

    /* IPv6 */
    inet_pton(AF_INET6, "a::1", &sa6.sin6_addr);
    if (ret != 1) {
        fprintf(stderr, "Error %d\n", ret);
    }
    printf("IPv6: sa6.sin6_addr.s6_addr: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", sa6.sin6_addr.s6_addr[i]);
    }
    printf("\n");
    inet_ntop(AF_INET6, &sa6.sin6_addr, ipv6, sizeof ipv6 / sizeof *ipv6);
    printf("IPv6: inet_ntop(): sa6.sin6_addr: %s\n", ipv6);

    /* IPv4-compatibility mode */
    inet_pton(AF_INET6, "::ffff:10.0.0.1", &sa6.sin6_addr);
    if (ret != 1) {
        fprintf(stderr, "Error %d\n", ret);
    }
    printf("IPv4-in-IPv6: sa6.sin6_addr.s6_addr: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", sa6.sin6_addr.s6_addr[i]);
    }
    printf("\n");
    inet_ntop(AF_INET6, &sa6.sin6_addr, ipv6, sizeof ipv6 / sizeof *ipv6);
    printf("IPv4-in-IPv6: inet_ntop(): sa6.sin6_addr: %s\n", ipv6);

    /* Truncated IPv4 */
    /* On Debian 8.3, the man page says,
     * "The buffer dst must be at least INET_ADDRSTRLEN bytes long."
     *
     * In fact, in the experiment below, it was observed that if the
     * buffer is not at least as long as the result string (including
     * the terminating null character), the destination buffer is left
     * unmodified. */
    ipv4[0] = 'x';
    ipv4[1] = '\0';
    ret = inet_pton(AF_INET, "10.30.30.40", &sa.sin_addr);
    if (ret != 1) {
        fprintf(stderr, "Error %d\n", ret);
    }
    inet_ntop(AF_INET, &sa.sin_addr, ipv4, 11);
    printf("Truncated IPv4: inet_ntop(): sa.sin_addr: %s\n", ipv4);
    inet_ntop(AF_INET, &sa.sin_addr, ipv4, 12);
    printf("Truncated IPv4: inet_ntop(): sa.sin_addr: %s\n", ipv4);

    /* Truncated IPv6 */
    /* The note written for Truncated IPv4 above applies here too. */
    ipv6[0] = 'x';
    ipv6[1] = '\0';
    ret = inet_pton(AF_INET6, "aaaa::bbbb", &sa6.sin6_addr);
    if (ret != 1) {
        fprintf(stderr, "Error %d\n", ret);
    }
    inet_ntop(AF_INET6, &sa6.sin6_addr, ipv6, 10);
    printf("Truncated IPv6: inet_ntop(): sa6.sin6_addr: %s\n", ipv6);
    inet_ntop(AF_INET6, &sa6.sin6_addr, ipv6, 11);
    printf("Truncated IPv6: inet_ntop(): sa6.sin6_addr: %s\n", ipv6);

    /* Invalid IPv4 */
    ret = inet_pton(AF_INET, "256.0.0.1", &sa.sin_addr);
    printf("256.0.0.1: ret: %d\n", ret);

    /* Invalid IPv6 */
    ret = inet_pton(AF_INET6, "::z", &sa.sin_addr);
    printf("::z: ret: %d\n", ret);

    /* IPv4-compatibility mode is invalid with AF_INET */
    ret = inet_pton(AF_INET, "::ffff:10.0.0.1", &sa.sin_addr);
    printf("::ffff:10.0.0.1: ret: %d\n", ret);
}
