/* 
Madison Byrd
BlazerID: mjbyrd 
project: HW2
To compile:
To run:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "traverse.h"
#include "display.h"

Options options;

int main(int argc, char *argv[])
{
    char *startDIR = ".";
    int opt;

    /*initializes the command line options */
    options.showInfo = 0;
    options.useSize = 0;
    options.usePattern = 0;

    /* this processes the command line options*/
    while ((opt=getopt(argc,argv,"Ss:f:")) != -1)
    {
        switch(opt)
        {
            case 'S':
                options.showInfo = 1;
                break;
            
            case 's':
                options.useSize = 1;
                options.maxSize = atol(optarg);
                break;

            case 'f':
                options.usePattern = 1;
                strcpy(options.pattern, optarg);

                if (optind < argc)
                {
                    options.maxDepth = atoi(argv[optind]);
                    optind++;
                }
                else
                {
                    fprintf(stderr, "Error: -f needs a depth.\n");
                    return 1;
                }
                break;
                
            default:
                fprintf(stderr, "Usafe: ./search [-S] [-s size] [-f pattern depth] [directory]\n");
                return 1;
        }
        
        
    }
    if (optind <argc)
    {
    startDIR = argv[optind];
    }

    /* Start the recursive directory traversal*/
    traverse(startDIR, processFile, 0);
        
    return 0;

}