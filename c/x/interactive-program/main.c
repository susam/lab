#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include "work.h"

#define WORK_LIB "./work.so"

int main()
{
    ino_t dl_ino = 0;
    void *dl_handle = NULL;
    struct work_api *api = NULL;

    for (;;)
    {
        struct stat attr;

        if (stat(WORK_LIB, &attr) == 0 && attr.st_ino != dl_ino) {

            if (dl_handle)
                dlclose(dl_handle);

            dl_handle = dlopen(WORK_LIB, RTLD_NOW);
            if (dl_handle) {
                if ((api = dlsym(dl_handle, "work_api"))) {
                    dl_ino = attr.st_ino;
                } else {
                    dlclose(dl_handle);
                    dl_handle = NULL;
                }
            }
        }

        if (api)
            api->work();

        sleep(1);
    }
}
