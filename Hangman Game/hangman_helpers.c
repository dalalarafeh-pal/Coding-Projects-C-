#include "hangman_helpers.h"
#include <stdio.h>

bool is_lowercase_letter(char c) {
	return c >= 'a' && c <= 'z';
}

bool validate_secret(const char *secret) {
	int counting_chars = 0;
	while(secret[counting_chars] != '\0') {
		counting_chars++;
	}

	if(strlen(secret) > MAX_LENGTH) {
		printf("the secret phrase is over 256 characters\n");
		return false;
	}	

	const char *c = secret;
	while (*c != 0){
		if (!(is_lowercase_letter(*c) || *c == ' ' || *c == '\'' || *c == '-')){
			printf("invalid character: '%c'\n", *c);
			printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and apostrophes\n");
			return false;
		}
		c++;	
	}
	return true; 	

}

bool string_contains_character(const char *s, char c) {
	while (*s != '\0') {
		if (*s == c) {
			return true;
		}
		s++;
	}
	return false; 
}

char read_letter(void) {
	int letter; 
	printf("Guess a letter: ");

	letter = getchar();
	while(getchar() != '\n') continue; 
	return (char) letter; 
}
