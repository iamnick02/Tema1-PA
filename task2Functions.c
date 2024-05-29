#include "main.h"

//returnam nr de echipe
int getTeamCount(TeamNode* teams) {
    int count = 0;
    TeamNode* current = teams;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//calculam punctele echipei
float getTeamPoints(Team* team) {
    float total_points = 0;
    for (int i = 0; i < team->teamMates; i++) {
        total_points += team->players[i].points;
    }
    return total_points / team->teamMates;
}

//returnam pozitia echipei cu cele mai mici puncte
int findMinTeam(TeamNode* head) {
    TeamNode* current = head;
    int position = 1;
    float min_points = getTeamPoints(&current->team);
    current = current->next;
    int i = 2;
    while (current != NULL) {
        float current_points = getTeamPoints(&current->team);
        if (current_points < min_points) {
            min_points = current_points;
            position = i;
        }
        current = current->next;
        i++;
    }
    return position;
}

//sterge echipa de pe o pozitie specifica
void deleteTeam(TeamNode** head, int position) {
    TeamNode* temp;
    if (position == 1) {
        temp = *head;
        *head = (*head)->next;
    } else {
        TeamNode* current = *head;
        TeamNode* prev = NULL;
        int i = 1;
        while (current != NULL && i < position) {
            prev = current;
            current = current->next;
            i++;
        }
        if (current == NULL) {
            return;
        }
        prev->next = current->next;
        temp = current;
    }
    for (int i = 0; i < temp->team.teamMates; i++) {
        free(temp->team.players[i].firstName);
        free(temp->team.players[i].secondName);
    }
    free(temp->team.players);
    free(temp->team.teamName);
    free(temp);
}

//eliminam echipele preliminare pe baza punctelor
void removePreliminary(TeamNode** head, int* n) {
    int power_of_2 = 1;
    while (power_of_2 * 2 <= *n) {
        power_of_2 *= 2;
    }
    while (*n != power_of_2) {
        int min_position = findMinTeam(*head);
        deleteTeam(head, min_position);
        (*n)--;
    }
}