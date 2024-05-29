#include "main.h"

//cream un nou nod pentru coada de meciuri
Node* createNode(const char* name, float points) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        memoryAllocationError();
        return NULL;
    }
    newNode->team.teamName = strdup(name);
    newNode->team.teamPoints = points;
    newNode->next = NULL;
    return newNode;
}

// cream o coada de meciuri
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        memoryAllocationError();
        return NULL;
    }
    queue->front = queue->rear = NULL;
    return queue;
}

//adaugam un nod la coada de meciuri
void enqueue(Queue* queue, const char* name, float points) {
    Node* newNode = createNode(name, points);
    if (newNode == NULL) return;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

//eliminam un nod din coada de meciuri
Node* dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;
    Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    return temp;
}

//cream o stiva
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        memoryAllocationError();
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

//adaugam un nod in stiva
void push(Stack* stack, const char* name, float points) {
    Node* newNode = createNode(name, points);
    if (newNode == NULL) return;
    newNode->next = stack->top;
    stack->top = newNode;
}

//eliminam un nod in stiva
Node* pop(Stack* stack) {
    if (stack->top == NULL) return NULL;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    return temp;
}

//simulam meciurile si afisam rezultatele in fisier
void simulateMatches(TeamNode* teams, char* outputFilename) {
    Queue* matches = createQueue();
    Stack* winners = createStack();
    Stack* losers = createStack();
    TeamNode* top8Teams = NULL;

    FILE* outputFile = fopen(outputFilename, "wt");
    if (outputFile == NULL) {
        fileOpeningError();
    }

    TeamNode* current = teams;
    while (current) {
        float teamPoints = getTeamPoints(&current->team);
        enqueue(matches, current->team.teamName, teamPoints);
        fprintf(outputFile, "%s\n", current->team.teamName);
        current = current->next;
    }

    int round = 1;
    while (matches->front && matches->front->next) {
        fprintf(outputFile, "\n--- ROUND NO:%d\n", round);
        Node* team1;
        Node* team2;

        while (matches->front && matches->front->next) {
            team1 = dequeue(matches);
            team2 = dequeue(matches);

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
            fprintf(outputFile, "%-33s -  %.2f\n", winner->team.teamName, winner->team.teamPoints);
            free(winner->team.teamName);
            free(winner);
            winner = pop(winners);
        }

        //salvam echipele castigatoare în top8Teams
        if (matches->front && matches->front->next == NULL) { //daca avem 8 echipe
            while (matches->front) {
                Node* temp = dequeue(matches);
                Team team;
                team.teamName = strdup(temp->team.teamName);
                team.teamPoints = temp->team.teamPoints;
                addTeamAtBeginning(&top8Teams, team);
                free(temp->team.teamName);
                free(temp);
            }
        }

        round++;
    }

    fclose(outputFile);
    freeQueue(matches);
    freeStack(winners);
    freeStack(losers);
}

//eliberarea memoriei pentru coada
void freeQueue(Queue* queue) {
    while (queue->front) {
        Node* temp = dequeue(queue);
        free(temp->team.teamName);
        free(temp);
    }
    free(queue);
}

//eliminarea memoriei pentru stiva
void freeStack(Stack* stack) {
    while (stack->top) {
        Node* temp = pop(stack);
        free(temp->team.teamName);
        free(temp);
    }
    free(stack);
}
