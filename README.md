# Tema 1 - Proiectarea Algoritmilor
Obiectivele acestei teme:
Intțelegerea conceptului de functionare si implementare a unor structuri de date(precum liste, stive, cozi, arbori binari de cautare)
Operarea cu aceste structuri de date
Implementarea unei functionalitati practice folosind aceste concepte

Cerintele:
[CLICK](https://ocw.cs.pub.ro/courses/sda-ab/tema1)

## Structura proiectului
### Proiectul este organizat in mai multe fisiere:

main.c - contine functia principala si logica de gestionare a intrarii/iesirii.
main.h - defineste structurile si functiile utilizate in proiect.
task1Functions.c - implementarea functiilor pentru citirea echipelor si manipularea acestora.
task2Functions.c - implementarea functiilor pentru eliminarea echipelor preliminare.
task3Functions.c - implementarea functiilor pentru simularea meciurilor si utilizarea unei cozi si a unei stive.
task4Functions.c - implementarea functiilor pentru simularea meciurilor si construirea unui arbore binar de cautare (BST).
task5Functions.c - implementarea functiilor pentru construirea si gestionarea unui arbore AVL.

## Descrierea fisierelor si functionalitatilor

### main.c
Fisierul main.c contine functia principala a proiectului care gestioneaza deschiderea fisierelor, citirea task-urilor dintr-un fisier de task-uri si apelarea functiilor corespunzatoare pentru fiecare task. Programul gestioneaza cinci task-uri:
Citirea echipelor dintr-un fisier de intrare si afisarea acestora intr-un fisier de iesire.
Eliminarea echipelor preliminare pana cand numarul ramas de echipe este o putere a lui 2.
Simularea meciurilor intre echipe si afisarea rezultatelor.
Simularea meciurilor si construirea unui arbore binar de cautare (BST) pentru echipele castigatoare.
Simularea meciurilor si construirea unui arbore AVL pentru echipele castigatoare.

### main.h
Fisierul main.h defineste structurile si functiile utilizate in proiect. Structurile includ:
Player - reprezinta un jucator.
Team - reprezinta o echipa, care include un nume, numarul de jucatori, lista de jucatori si punctele echipei.
TeamNode - reprezinta un nod din lista de echipe.
Node - reprezinta un nod din coada de meciuri.
Queue - reprezinta o coada de meciuri.
Stack - reprezinta o stiva de meciuri.
BSTNode - reprezinta un nod din arborele binar de cautare.
AVLNode - reprezinta un nod din arborele AVL.
Functiile definite in main.h sunt utilizate pentru a gestiona echipele, coada, stiva si arborii binari.

### task1Functions.c
Acest fisier contine functiile pentru citirea echipelor dintr-un fisier si manipularea acestora. Functiile includ:
openFiles - deschide fisierele necesare pentru intrare si iesire.
addTeamAtBeginning - adauga o echipa la inceputul listei de echipe.
readTeams - citeste echipele dintr-un fisier si le adauga in lista de echipe.
printTeamsToFile - afiseaza echipele intr-un fisier.
printTeams - afiseaza echipele pe ecran.
freeTeams - elibereaza memoria alocata pentru echipe.

### task2Functions.c
Acest fisier contine functiile pentru eliminarea echipelor preliminare. Functiile includ:
getTeamCount - returneaza numarul de echipe din lista.
getTeamPoints - calculeaza punctele unei echipe.
findMinTeam - gaseste echipa cu cele mai putine puncte.
deleteTeam - elimina o echipa din lista.
removePreliminary - elimina echipele pana cand numarul ramas este o putere a lui 2.

### task3Functions.c
Acest fisier contine functiile pentru simularea meciurilor intre echipe folosind o coada si o stiva. Functiile includ:
createNode - creeaza un nod pentru coada de meciuri.
createQueue - creeaza o coada de meciuri.
enqueue - adauga un nod in coada.
dequeue - elimina un nod din coada.
createStack - creeaza o stiva.
push - adauga un nod in stiva.
pop - elimina un nod din stiva.
simulateMatches - simuleaza meciurile intre echipe si afiseaza rezultatele.
freeQueue - elibereaza memoria alocata pentru coada.
freeStack - elibereaza memoria alocata pentru stiva.

### task4Functions.c
Acest fisier contine functiile pentru simularea meciurilor si construirea unui arbore binar de cautare (BST) pentru echipele castigatoare. Functiile includ:
simulateMatchesAndBuildBST - simuleaza meciurile si construieste un arbore binar de cautare.
newBSTNode - creeaza un nod nou pentru arborele BST.
insertBST - insereaza un nod in arborele BST.
printBSTInDescendingOrder - afiseaza arborele BST in ordine descrescatoare.
freeBST - elibereaza memoria alocata pentru arborele BST.
Task4 - construieste arborele BST si afiseaza echipele castigatoare.


### task5Functions.c
Acest fisier contine functiile pentru construirea si gestionarea unui arbore AVL pentru echipele castigatoare. Functiile includ:
max - returneaza valoarea maxima dintre doua valori.
nodeHeight - returneaza inaltimea unui nod din arborele AVL.
newAVLNode - creeaza un nod nou pentru arborele AVL.
LeftRotation - realizeaza rotatia la stanga a unui nod din arborele AVL.
RightRotation - realizeaza rotatia la dreapta a unui nod din arborele AVL.
LRRotation - realizeaza rotatia stanga-dreapta a unui nod din arborele AVL.
RLRotation - realizeaza rotatia dreapta-stanga a unui nod din arborele AVL.
getBalance - calculeaza factorul de echilibru al unui nod din arborele AVL.
insertAVL - insereaza un nod in arborele AVL.
printLevel - afiseaza nivelul unui arbore AVL.
Task5 - construieste arborele AVL si afiseaza echipele castigatoare.
freeAVL - elibereaza memoria alocata pentru arborele AVL.
simulateMatchesAndBuildAVL - simuleaza meciurile si construieste un arbore AVL.
convertBSTtoAVL - converteste un arbore BST intr-un arbore AVL.
