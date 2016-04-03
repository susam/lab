#include <stdio.h>
#include "work.h"

static int i = 0;

static void work()
{
    printf("%d\n", i++);
}

const struct work_api work_api = {work};
