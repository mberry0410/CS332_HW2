#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

#include "traverse.h"
#include "display.h"


#define FTW_F  1
#define FTW_D  2
#define FTW_DNR 3
#define FTW_NS 4
#define FTW_SL 5


/*
Madison Byrd
BlazerID: mjbyrd 
project: HW2
To compile:
To run:
*/




extern Options options;

/*this checks whether a file should be displayed */
static int passesFilters(const char *pathname,
                        const struct stat *statbuf,
                        int depth)
{
    const char *name;

    name = strrchr(pathname, '/');

    if (name != NULL)
        name++;
    else
        name = pathname;
        
    if (options.useSize)
    {
        if(!S_ISDIR(statbuf->st_mode) &&
            statbuf->st_size >options.maxSize)
        {
                return 0;
        }
    }

    // Checks the file name pattern and depth
    if (options.usePattern)
    {
        if(strstr(name,options.pattern)== NULL)
            return 0;

        if (depth > options.maxDepth)
            return 0;
    }
    return 1;
}

int traverse(char *pathname, MYFUNC *func , int depth)
{  
    struct stat statbuf;
    DIR *dp;
    struct dirent * dirp;
    char newpath[PATH_MAX];

    /*Will get information about the current file*/
    if (lstat(pathname, &statbuf) < 0)
    {
        return func (pathname, &statbuf, FTW_NS, depth);
    }

    if (!S_ISDIR(statbuf.st_mode))
    {
        if(passesFilters(pathname,&statbuf, depth))
        {
            if (S_ISLNK(statbuf.st_mode))
                return func(pathname, &statbuf, FTW_SL, depth);
            else
                return func(pathname, &statbuf, FTW_F, depth);
        }

        return 0;

    }

    /* Displays the directory if it passes the filters */
    if (passesFilters(pathname, &statbuf, depth))
    {
        func(pathname, &statbuf, FTW_D, depth);
    }

    /*Opens directory*/
    dp = opendir(pathname);

    if (dp==NULL)
    {
        return func(pathname, &statbuf, FTW_DNR, depth);
    }

    /*reads each entry in the directory */
    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0 ||
            strcmp(dirp->d_name, "..") == 0)
        {
            continue;
        }
        
        //build the full pathname
        snprintf(newpath,sizeof(newpath) , "%s/%s", pathname, dirp->d_name);

        traverse(newpath, func, depth + 1);
    }

    closedir(dp);

    return 0;
}

    







