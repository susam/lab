#include <stdio.h>
#include <inttypes.h>
#include <arpa/inet.h>

int main()
{
    uint16_t hport, nport;
    uint32_t haddr, naddr;

    hport = 0x1234; /* port 4660 */
    nport = htons(hport);
    hport = ntohs(nport);

    printf("hport: 0x%jx\n", (intmax_t) hport);
    printf("nport: 0x%jx\n", (intmax_t) nport);

    haddr = 0x10203040; /* 16.32.48.64 */
    naddr = htonl(haddr);
    haddr = ntohl(naddr);

    printf("haddr: 0x%jx\n", (intmax_t) haddr);
    printf("naddr: 0x%jx\n", (intmax_t) naddr);
}
