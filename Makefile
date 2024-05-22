build:
	gcc main.c main.h task1Functions.c task2Functions.c errorFunctions.c -o lanParty
clean:
	rm -f lanParty
