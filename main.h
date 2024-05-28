#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structura pentru un jucător
typedef struct Player {
    char *firstName;
    char *secondName;
    int points;
} Player;

// Structura pentru o echipă
typedef struct Team {
    int teamMates;
    char *teamName;
    Player *players;
    float teamPoints;  // Total points of the team
    struct Team* next;
} Team;

// Structura pentru un nod al listei de echipe
typedef struct TeamNode {
    Team team;
    struct TeamNode* next;
} TeamNode;

// Structura pentru un nod al cozii de meciuri
typedef struct Node {
    Team team;
    struct Node* next;
} Node;

// Structura pentru o coadă de meciuri
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Structura pentru o stivă
typedef struct Stack {
    Node* top;
} Stack;

typedef struct BSTNode {
    char* teamName;
    float teamPoints;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;
} BSTNode;

typedef struct AVLNode {
    char* teamName;
    float teamPoints;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

void fileOpeningError();
void memoryAllocationError();
void openFiles(char *filename1, FILE **file1, char *filename2, FILE **file2, char *filename3, FILE **file3);
TeamNode* addTeamAtBeginning(TeamNode** head, Team team);
TeamNode* readTeams(FILE* file, FILE* outputFile);
void printTeams(TeamNode* teams);
void printTeamsToFile(TeamNode* teams, FILE* file); 
void freeTeams(TeamNode* teams);
int getTeamCount(TeamNode* teams);
float getTeamPoints(Team* team);
int findMinTeam(TeamNode* head);
void deleteTeam(TeamNode** head, int position);
void removePreliminary(TeamNode** head, int* n);
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
BSTNode* newBSTNode(const char* name, float points);
BSTNode* insertBST(BSTNode* node, const char* name, float points);
void printBSTInDescendingOrder(BSTNode* root, FILE* outputFile);
void freeBST(BSTNode* root);
BSTNode* Task4(const char *filename, TeamNode *lastEightTeams);
void simulateMatchesAndBuildBST(TeamNode* teams, const char* outputFilename);
void freeQueue(Queue* queue);
void freeStack(Stack* stack);
BSTNode* newBSTNode(const char* name, float points);
BSTNode* insertBST(BSTNode* node, const char* name, float points);
void printBSTInDescendingOrder(BSTNode* root, FILE* outputFile);
void freeBST(BSTNode* root);
void simulateMatchesAndBuildBST(TeamNode* teams, const char* outputFilename);
void freeQueue(Queue* queue);
void freeStack(Stack* stack);
BSTNode* newBSTNode(const char* name, float points);
BSTNode* insertBST(BSTNode* node, const char* name, float points);
void printBSTInDescendingOrder(BSTNode* root, FILE* outputFile);
void freeBST(BSTNode* root);
void simulateMatchesAndBuildBST(TeamNode* teams, const char* outputFilename);
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
void printTree(AVLNode *root, int level);
void BST_AVL(BSTNode* root, AVLNode** root1);