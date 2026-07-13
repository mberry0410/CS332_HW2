#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <sys/stat.h>


#define FTW_F  1
#define FTW_D  2
#define FTW_DNR 3
#define FTW_NS 4
#define FTW_SL 5


/*Function pointer used during traversal*/
typedef int MYFUNC(const char *pathname, const struct stat *statbuf, int type, int depth);

/*the recursive directory traversal */
int traverse(char *pathname, MYFUNC *func, int depth);

#endif