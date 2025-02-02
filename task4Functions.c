#include "main.h"

//simulam meciurile si construim BST
void simulateMatchesAndBuildBST(TeamNode* teams, const char* outputFilename) {
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
            } else {//egalitate la puncte
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

        //salvam cele 8 echipe ramase cand nr de echipe e 8
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

    //afisam echipele top 8 folosind BST
    BSTNode* BSTree = NULL;
    BSTree = Task4(outputFilename, top8Teams);
    freeTeams(top8Teams);
}

//cream un nou nod pentru BST
BSTNode* newBSTNode(const char* name, float points) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node == NULL) {
        memoryAllocationError();
        return NULL;
    }
    node->teamName = strdup(name);
    node->teamPoints = points;
    node->left = node->right = NULL;
    return node;
}

//inseram un nod in BST
BSTNode* insertBST(BSTNode* node, const char* name, float points) {
    if (node == NULL) 
        return newBSTNode(name, points);

    if (points < node->teamPoints || (points == node->teamPoints && strcmp(name, node->teamName) < 0)) {
        node->left = insertBST(node->left, name, points);
    } else {
        node->right = insertBST(node->right, name, points);
    }
    return node;
}

//afisam elementele din BST in ordine descrescatoare
void printBSTInDescending(BSTNode* root, FILE* outputFile) {
    if (root == NULL) return;
    printBSTInDescending(root->right, outputFile);
    fprintf(outputFile, "%-33s -  %.2f\n", root->teamName, root->teamPoints);
    printBSTInDescendin(root->left, outputFile);
}

//eliberam memoria alocata pt nodurile din BST
void freeBST(BSTNode* root) {
    if (root == NULL) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root->teamName);
    free(root);
}

//construim BST ul pt top 8 echipe
BSTNode* Task4(const char *filename, TeamNode *lastEightTeams) {
    FILE *filePrint = fopen(filename, "at");
    if (filePrint == NULL) {
        fileOpeningError();
    }

    fprintf(filePrint, "\nTOP 8 TEAMS:\n");

    BSTNode *BSTree = NULL;
    TeamNode *currentTeam = lastEightTeams;
    while (currentTeam != NULL) {
        BSTree = insertBST(BSTree, currentTeam->team.teamName, currentTeam->team.teamPoints);
        currentTeam = currentTeam->next;
    }

    printBSTInDescending(BSTree, filePrint);
    fclose(filePrint);

    return BSTree;
}