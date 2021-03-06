#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    assert(argc > 1);
    char *name;
    char s[128];
    while(1) {
        for(int i = 1; i < argc; i++) {
            name = argv[i];
            struct addrinfo* res;
            struct addrinfo hints;
            memset(&hints, 0, sizeof(hints));
            int v4count=0;
            int v6count=0;
            int errcount=0;
            int nonamecount=0;
            int nodatacount=0;

            for(int af = 0; af < 2; ++af) {
                hints.ai_family = af ? AF_INET : AF_INET6;
                hints.ai_socktype = SOCK_STREAM;
                int ret = getaddrinfo(name, 0, &hints, &res);
                if(ret == 0) {
                    struct addrinfo* address = res;
                    do {
                        if(af) v6count++;
                        else v4count++;
                    } while((address = address->ai_next));
                    freeaddrinfo(res);
                }
                else
                {
                    switch(ret) {
                        case EAI_NONAME:
                            nonamecount++;
                            break;
#ifdef EAI_NODATA
                        case EAI_NODATA:
                            nodatacount++;
                            break;
#endif
                        default:
                            fprintf(stderr, "error: %s(%s): %s (%d)\n", name, af ? "v4" : "v6", gai_strerror(ret), ret);
                            errcount++;
                    }
                }
            }
            printf("%s: v4=%d v6=%d noname=%d nodata=%d errors=%d | ", name, v4count, v6count, nonamecount, nodatacount, errcount);
        }
        printf("\n");
    }
}
