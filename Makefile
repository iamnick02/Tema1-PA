build:
	gcc main.c task1Functions.c task2Functions.c task3Functions.c errorFunctions.c -o lanParty
clean:
	rm -f lanParty
