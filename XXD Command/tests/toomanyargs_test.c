#include <stdio.h>
#include <stdlib.h>

int main() {
	int file = system("./xd arg1 arg2");

	if (file != 0) {
		printf("TOO MANY ARGUMENTS.\n");
	} else {
		printf("SUCCESSFUL.\n");
	}
	return 0;
}
		
