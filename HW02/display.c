#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>

#include "display.h"
#include "traverse.h"

/* 
Madison Byrd
BlazerID: mjbyrd 
project: HW2
To compile:
To run:
*/

extern Options options;

int processFile(const char *pathname, const struct stat *statbuf, int type, int depth)

{
    int i;
    const char *name;

    /* Prints the indentation */
    for (i = 0; i < depth; i++ )
    {
        printf("\t");
    }

    /* only gets the file name */
    name = strrchr(pathname, '/');

    if (name != NULL)
    {
        name++;
    }
    else
    {
        name = pathname;
    }

    /*This prints the file name */
    printf("%s", name);

    if (type == FTW_SL)
    {
        char target[PATH_MAX];

        ssize_t len = readlink(pathname, target, sizeof(target)-1);

        if (len >= 0)
        {
            target[len] = '\0';
            printf(" (%s)", target);
        }
    }

    /* when -S is used it will print more information */
    if (options.showInfo)
    {
    printf("%ld bytes", (long)statbuf->st_size);
    

    }
    printf("\n");

    return 0;

}