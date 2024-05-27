#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    FILE *taskFile, *fileIn, *fileOut;
    openFiles(argv[1], &taskFile, argv[2], &fileIn, argv[3], &fileOut);
    TeamNode* teams = NULL;

    int tasks[5];
    for (int i = 0; i < 5; i++) {
        fscanf(taskFile, "%d", &tasks[i]);
    }
    
    if (tasks[0] == 1) {
        teams = readTeams(fileIn, fileOut);
        fclose(fileOut); 
    }

    if (tasks[1] == 1) {
        if (!teams) {
            teams = readTeams(fileIn, fileOut);
        }
        int teamCount = getTeamCount(teams);
        removePreliminary(&teams, &teamCount);
        FILE* newFileOut = fopen(argv[3], "wt");
        if (newFileOut == NULL) {
            fileOpeningError();
        }
        printTeamsToFile(teams, newFileOut);
        fclose(newFileOut);
    }

    if (tasks[2] == 1) {
        FILE* newFileOut = fopen(argv[3], "wt");
        if (newFileOut == NULL) {
            fileOpeningError();
        }
        simulateMatches(teams, argv[3]);
        fclose(newFileOut);
    }

    freeTeams(teams);
    fclose(fileIn);
    fclose(taskFile);

    return 0;
}
