/*
Madison Byrd
BlazerID: mjbyrd 
project: HW2
To compile:
To run:
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <sys/stat.h>

typedef struct
{
    int showInfo;
    int useSize;
    long  maxSize;
    int usePattern;
    char pattern[256];
    int maxDepth;

} Options;

extern Options options;

int processFile(const char *pathname, const struct stat *statbuf, int type, int depth);

#endif