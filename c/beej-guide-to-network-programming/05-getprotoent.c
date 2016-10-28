#include <stdio.h>
#include <netdb.h>

void print_protoent(struct protoent *proto)
{
    char **p;

    printf("p_name: %s\n", proto->p_name);

    printf("p_aliases: ");
    for (p = proto->p_aliases; *p != NULL; p++) {
        printf("%s \n", *p);
    }

    printf("p_proto: %d\n", proto->p_proto);
    printf("\n");
}

int main()
{
    struct protoent *p;
    while ((p = getprotoent()) != NULL) {
        print_protoent(p);
    }
    printf("-----\n\n");
    print_protoent(getprotobyname("tcp"));
    print_protoent(getprotobynumber(17));
}
