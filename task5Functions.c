#include "main.h"

void printTree(AVLNode *root, int level)
{
    if (root == NULL) {
        return;
    }

    printTree(root->right, level+1);

    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("%s-%.2f\n", root->teamName, root->teamPoints);

    printTree(root->left, level + 1);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Functie pentru a obtine inaltimea unui nod
int nodeHeight(AVLNode* node) {
    if (node == NULL)
        return -1;
    return node->height;
}

// Functie pentru a crea un nod nou pentru arborele AVL
AVLNode* newAVLNode(const char* name, float points) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (node == NULL) {
        memoryAllocationError();
        return NULL;
    }
    node->teamName = strdup(name);
    node->teamPoints = points;
    node->height = 0;
    node->left = node->right = NULL;
    return node;
}

AVLNode* LeftRotation(AVLNode* z) {
    AVLNode* y = z->right;
    AVLNode* T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    printf("Intrat l\n");
    return y;
}

AVLNode* RightRotation(AVLNode* z) {
    AVLNode* y = z->left;
    AVLNode* T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    printf("Intrat r\n");
    return y;
}

AVLNode* LRRotation(AVLNode* Z) {
    Z->left = LeftRotation(Z->left);
    printf("Intrat lr\n");
    return RightRotation(Z);
}

AVLNode* RLRotation(AVLNode* Z) {
    Z->right = RightRotation(Z->right);
    printf("Intrat rl\n");
    return LeftRotation(Z);
}

// Functie pentru a obtine factorul de echilibru al unui nod
int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return nodeHeight(node->left) - nodeHeight(node->right);
}

AVLNode* insertAVL(AVLNode* node, const char* name, float points) {
    if (node == NULL) {
        return newAVLNode(name, points);
    }

    if (points < node->teamPoints){
        node->left = insertAVL(node->left, name, points);
    }
    else
    { 
        if (points > node->teamPoints)
        {
            node->right = insertAVL(node->right, name, points);
        }
        else
        {
            if (strcmp(name, node->teamName) > 0) 
                node->right = insertAVL(node->right, name, points);
            else
                node->left = insertAVL(node->left, name, points);
        }
    }
    printTree(node, 0);
    printf("-----\n");
    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

    int balance = getBalance(node);

    // Rotatii pentru echilibrare
    if (balance > 1) {
        if (points < node->left->teamPoints) 
        {
            return RightRotation(node);
        } 
        else 
        {
            if (points == node->left->teamPoints && strcmp(name, node->left->teamName) < 0)
        {
            return RightRotation(node);
        } 
        else 
        {
            if (points == node->left->teamPoints && strcmp(name, node->left->teamName) > 0) 
        {
            return RightRotation(node);
        } 
        else //if (points > node->left->teamPoints) 
        {
            return RLRotation(node);
        }
    }
    }
    }

    if (balance < -1) {
        if (points > node->right->teamPoints) {
            return LeftRotation(node);
        } else 
        {
        if (points == node->right->teamPoints && strcmp(name, node->right->teamName) > 0) {
            return LeftRotation(node);
        } else 
        {
        if (points == node->right->teamPoints && strcmp(name, node->right->teamName) < 0) {
            printf("da\n");
            return LeftRotation(node);
        } else //if (points < node->right->teamPoints) {
            return LRRotation(node);
        }
    }
    }
    //printTree(node, 0);
    //printf("-----\n");
    return node;
}



void printLevel(AVLNode* root, int level, FILE* outputFile) {
    if (root == NULL) 
        return;
    if (level == 0) {
        fprintf(outputFile, "%-33s\n", root->teamName);
    } else {
        printLevel(root->right, level - 1, outputFile);
        printLevel(root->left, level - 1, outputFile);
    }
}

void freeAVL(AVLNode* root) {
    if (root == NULL) return;
    freeAVL(root->left);
    freeAVL(root->right);
    free(root->teamName);
    free(root);
}

void BST_AVL(BSTNode* root, AVLNode** root1) {
    if (root == NULL) return;
    BST_AVL(root->right, root1);
    *root1 = insertAVL(*root1, root->teamName, root->teamPoints);
    BST_AVL(root->left, root1);
}

void Task5(const char* filename, BSTNode* root) {
    FILE* filePrint = fopen(filename, "at");
    if (filePrint == NULL) {
        fileOpeningError();
    }
    AVLNode* AVLTree = NULL;
    //TeamNode* currentTeam = lastEightTeams;
    /*while (currentTeam != NULL) {
        AVLTree = insertAVL(AVLTree, currentTeam->team.teamName, currentTeam->team.teamPoints);
        currentTeam = currentTeam->next;
    }*/
    BST_AVL(root, &AVLTree);
    fprintf(filePrint, "\nTHE LEVEL 2 TEAMS ARE:\n");
    printTree(AVLTree, 0);
    printLevel(AVLTree, 2, filePrint);  // Afiseaza echipele la nivelul 2
    fclose(filePrint);
    freeAVL(AVLTree);
}

void simulateMatchesAndBuildAVL(TeamNode* teams, const char* outputFilename) {
    Queue* matches = createQueue();
    Stack* winners = createStack();
    Stack* losers = createStack();
    TeamNode* top8Teams = NULL;
    int queueSize = 0;

    FILE* outputFile = fopen(outputFilename, "wt");
    if (outputFile == NULL) {
        fileOpeningError();
    }

    TeamNode* currentTeamNode = teams;
    while (currentTeamNode) {
        float teamPoints = getTeamPoints(&currentTeamNode->team);
        enqueue(matches, currentTeamNode->team.teamName, teamPoints);
        queueSize++;
        fprintf(outputFile, "%s\n", currentTeamNode->team.teamName);
        currentTeamNode = currentTeamNode->next;
    }

    int round = 1;
    while (queueSize > 1) {
        fprintf(outputFile, "\n--- ROUND NO:%d\n", round);
        Node* team1;
        Node* team2;

        while (queueSize > 1) {
            team1 = dequeue(matches);
            team2 = dequeue(matches);
            queueSize -= 2;

            fprintf(outputFile, "%-32s - %32s\n", team1->team.teamName, team2->team.teamName);

            if (team1->team.teamPoints > team2->team.teamPoints) {
                team1->team.teamPoints++;
                push(winners, team1->team.teamName, team1->team.teamPoints);
                push(losers, team2->team.teamName, team2->team.teamPoints);
            } else if (team1->team.teamPoints < team2->team.teamPoints) {
                team2->team.teamPoints++;
                push(winners, team2->team.teamName, team2->team.teamPoints);
                push(losers, team1->team.teamName, team1->team.teamPoints);
            } else {
                push(winners, team2->team.teamName, team2->team.teamPoints + 1);
                push(losers, team1->team.teamName, team1->team.teamPoints);
            }

            free(team1->team.teamName);
            free(team1);
            free(team2->team.teamName);
            free(team2);
        }

        fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", round);
        Node* winner = pop(winners);
        while (winner) {
            enqueue(matches, winner->team.teamName, winner->team.teamPoints);
            queueSize++;
            fprintf(outputFile, "%-33s -  %.2f\n", winner->team.teamName, winner->team.teamPoints);
            free(winner->team.teamName);
            free(winner);
            winner = pop(winners);
        }

        round++;

        // Salvăm cele 8 echipe rămase când numărul de echipe este 8
        if (queueSize == 8) {
            Node* currentNode = matches->front;
            while (currentNode) {
                Team team;
                team.teamName = strdup(currentNode->team.teamName);
                team.teamPoints = currentNode->team.teamPoints;
                addTeamAtBeginning(&top8Teams, team);
                currentNode = currentNode->next;
            }
        }
    }

    fclose(outputFile);
    freeQueue(matches);
    freeStack(winners);
    freeStack(losers);
    BSTNode* BSTree = NULL;
    BSTree = Task4(outputFilename, top8Teams);
    Task5(outputFilename, BSTree);
    freeTeams(top8Teams);
}
