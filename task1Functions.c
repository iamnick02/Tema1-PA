#include "main.h"

void openFiles(char *filename1, FILE **file1, char *filename2, FILE **file2, char *filename3, FILE **file3) {
    *file1 = fopen(filename1, "rt");
    if(*file1 == NULL)
        fileOpeningError();

    *file2 = fopen(filename2, "rt");
    if(*file2 == NULL)
        fileOpeningError();

    *file3 = fopen(filename3, "wt");
    if(*file3 == NULL)
        fileOpeningError();
}

TeamNode* addTeamAtBeginning(TeamNode** head, Team team) {
    TeamNode* newNode = (TeamNode*) malloc(sizeof(TeamNode));
    newNode->team = team;
    newNode->next = *head;
    *head = newNode;
    return *head;
}

TeamNode* readTeams(FILE* file, FILE* outputFile) {
    int teamCount;
    fscanf(file, "%d\n", &teamCount); 
    TeamNode* teams = NULL;

    for (int i = 0; i < teamCount; i++) {
        int playerCount;
        char teamName[50];
        fscanf(file, "%d ", &playerCount);

        fgets(teamName, 50, file);
        teamName[strlen(teamName) - 2] = '\0';
        if(teamName[strlen(teamName) - 1] == ' '){
            teamName[strlen(teamName) - 1] = '\0';
        }

        Team team;
        team.teamName = strdup(teamName);
        team.teamMates = playerCount;
        team.players = (Player*)malloc(sizeof(Player) * playerCount);

        for (int j = 0; j < playerCount; j++) {
            char firstName[50];
            char secondName[50];
            int points;
            fscanf(file, "%s %s %d\n", firstName, secondName, &points);

            team.players[j].firstName = strdup(firstName);
            team.players[j].secondName = strdup(secondName);
            team.players[j].points = points;
        }

        teams = addTeamAtBeginning(&teams, team);
    }

    TeamNode* current = teams;
    while (current != NULL) {
        fprintf(outputFile, "%s\n", current->team.teamName);
        current = current->next;
    }

    return teams;
}

void printTeamsToFile(TeamNode* teams, FILE* file) {
    TeamNode* current = teams;
    while (current != NULL) {
        fprintf(file, "%s\n", current->team.teamName);
        current = current->next;
    }
}

void printTeams(TeamNode* teams) {
    TeamNode* current = teams;
    while (current != NULL) {
        printf("%s\n", current->team.teamName);
        current = current->next;
    }
}

void freeTeams(TeamNode* teams) {
    TeamNode* current = teams;
    while (current != NULL) {
        TeamNode* next = current->next;
        for (int i = 0; i < current->team.teamMates; i++) {
            free(current->team.players[i].firstName);
            free(current->team.players[i].secondName);
        }
        free(current->team.players);
        free(current->team.teamName);
        free(current);
        current = next;
    }
}