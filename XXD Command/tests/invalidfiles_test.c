#include <stdio.h>
#include <stdlib.h>

int main() {
	int file = system("./xd invalidfile.txt");

	if (file != 0) {
		printf("INVALID FILE.\n");
	} else {
		printf("SUCCESSFUL.\n");
	}
	return 0;
}

