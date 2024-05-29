#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura pentru un jucator
typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

//structura pentru o echipa
typedef struct Team {
    int teamMates;
    char *teamName;
    Player *players;
    float teamPoints; 
    struct Team* next;
} Team;

//structura pentru un nod al listei de echipe
typedef struct TeamNode {
    Team team;
    struct TeamNode* next;
} TeamNode;

//structura pentru un nod al cozii de meciuri
typedef struct Node {
    Team team;
    struct Node* next;
} Node;

//structura pentru o coada de meciuri
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

//structura pentru o stiva
typedef struct Stack {
    Node* top;
} Stack;

//structura pentru un nod din arborele binar de cautare
typedef struct BSTNode {
    char* teamName;
    float teamPoints;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;
} BSTNode;

//structura pentru un nod din arborele AVL
typedef struct AVLNode {
    char* teamName;
    float teamPoints;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

void fileOpeningError();
void memoryAllocationError();

//Task 1 
void openFiles(char *filename1, FILE **file1, char *filename2, FILE **file2, char *filename3, FILE **file3);
TeamNode* addTeamAtBeginning(TeamNode** head, Team team);
TeamNode* readTeams(FILE* file, FILE* outputFile);
void printTeams(TeamNode* teams);
void printTeamsToFile(TeamNode* teams, FILE* file); 
void freeTeams(TeamNode* teams);

//Task 2 
int getTeamCount(TeamNode* teams);
float getTeamPoints(Team* team);
int findMinTeam(TeamNode* head);
void deleteTeam(TeamNode** head, int position);
void removePreliminary(TeamNode** head, int* n);

//Task 3 
Node* createNode(const char* name, float points);
Queue* createQueue();
void enqueue(Queue* queue, const char* name, float points);
Node* dequeue(Queue* queue);
Stack* createStack();
void push(Stack* stack, const char* name, float points);
Node* pop(Stack* stack);
void simulateMatches(TeamNode* teams, char* outputFilename);
void freeQueue(Queue* queue);
void freeStack(Stack* stack);

//Task 4
BSTNode* newBSTNode(const char* name, float points);
BSTNode* insertBST(BSTNode* node, const char* name, float points);
void printBSTInDescending(BSTNode* root, FILE* outputFile);
void freeBST(BSTNode* root);
BSTNode* Task4(const char *filename, TeamNode *lastEightTeams);
void simulateMatchesAndBuildBST(TeamNode* teams, const char* outputFilename);

//Task 5
int max(int a, int b);
int nodeHeight(AVLNode* node);
AVLNode* newAVLNode(const char* name, float points);
AVLNode* LeftRotation(AVLNode* z);
AVLNode* RightRotation(AVLNode* z);
AVLNode* LRRotation(AVLNode* Z);
AVLNode* RLRotation(AVLNode* Z);
int getBalance(AVLNode* node);
AVLNode* insertAVL(AVLNode* node, const char* name, float points);
void printLevel(AVLNode* root, int level, FILE* outputFile);
void Task5(const char* filename, BSTNode* root);
void freeAVL(AVLNode* root);
void simulateMatchesAndBuildAVL(TeamNode* teams, const char* outputFilename);
void convertBSTtoAVL(BSTNode* bstRoot, AVLNode** avlRoot);