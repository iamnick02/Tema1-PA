#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[])
{
    if(argc != 4)
        return 1;

    FILE *fileOut, *fileIn, *taskFile; 
    openFiles(argv[1], &taskFile, argv[2], &fileIn, argv[3], &fileOut);
    TeamNode* teams = readTeams(fileIn, fileOut);

    printTeams(teams);
    freeTeams(teams);

    return 0;
}