#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {
    //verificam daca numarul de argumente este corect
    if (argc != 4) {
        return 1;
    }

    FILE *taskFile, *fileIn, *fileOut;
    //deschidem fisierele specifice pentru task uri, input si output
    openFiles(argv[1], &taskFile, argv[2], &fileIn, argv[3], &fileOut);
    TeamNode* teams = NULL;

    //citim cele 5 task uri din fisierul taskFile
    int tasks[5];
    for (int i = 0; i < 5; i++) {
        fscanf(taskFile, "%d", &tasks[i]);
    }
    
    //Task 1: citim echipele daca task ul este setat
    if (tasks[0] == 1) {
        teams = readTeams(fileIn, fileOut);
        fclose(fileOut); 
    }

    //Task 2: eliminam echipele preliminare daca task ul este setat
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

    //Task 3: simulam meciurile daca task ul este setat
    if (tasks[2] == 1) {
       FILE* newFileOut = fopen(argv[3], "wt");
        if (newFileOut == NULL) {
            fileOpeningError();
        }
        simulateMatches(teams, argv[3]);
        fclose(newFileOut);
    }

    //Task 4: simulam meciurile si construim BST ul daca task ul este setat
    if (tasks[3] == 1) {
        simulateMatchesAndBuildBST(teams, argv[3]);
    }

     //Task 5: simulam meciurile si construim AVL ul daca task ul este setat
    if (tasks[4] == 1) {
        simulateMatchesAndBuildAVL(teams, argv[3]);
    }

    // eliberam memoria si inchidem fisierele deschise
    freeTeams(teams);
    fclose(fileIn);
    fclose(taskFile);

    return 0;
}