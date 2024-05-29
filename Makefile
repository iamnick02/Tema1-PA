build:
	gcc main.c task1Functions.c task2Functions.c task3Functions.c task4Functions.c task5Functions.c errorFunctions.c -o lanParty
clean:
	rm -f lanParty
