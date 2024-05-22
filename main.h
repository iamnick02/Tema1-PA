#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player{
    char *firstName;
    char *secondName;
    int points;
}Player;

typedef struct Team{
    int teamMates;
    char *teamName;
    Player *players;
}Team;

typedef struct TeamNode {
    Team team;
    struct TeamNode* next;
} TeamNode;

void fileOpeningError();
void memoryAllocationError();
void openFiles(char *filename1, FILE **file1, char *filename2, FILE **file2, char *filename3, FILE **file3);
TeamNode* addTeamAtBeginning(TeamNode** head, Team team);
TeamNode* readTeams(FILE* file, FILE* outputFile);
void printTeams(TeamNode* teams);
void printTeamsToFile(TeamNode* teams, FILE* file); 
void freeTeams(TeamNode* teams);
int isPowerOfTwo(int n);
int getTeamCount(TeamNode* teams);
float getTeamPoints(Team* team);
int findMinTeam(TeamNode* head);
void deleteNodeAtPosition(TeamNode** head, int position);
void removePreliminary(TeamNode** head, int* n);
void clearStack(TeamNode** head);