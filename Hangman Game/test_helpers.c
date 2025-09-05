#include "hangman_helpers.h"
#include <stdio.h>
#include <stdbool.h>

void test_is_lowercase_letter() {
	bool result; 
	
	result = is_lowercase_letter('A');
	if(result != false) {
		printf("Test is_lowercase_letter 'A' Failed\n");
	} else {
		printf("Test is_lowercase_letter 'A' Passed\n");
	}

	result = is_lowercase_letter('a');
	if(result != true) {
		printf("Test is_lowercase_letter 'a' Failed\n");
	} else {
		printf("Test is_lowercase_letter 'a' Passed\n");
	}
}

void test_validate_secret() {
	bool result; 
	result = validate_secret("valid");
	if (result != true) {
		printf("Test validate_secret valid Passed\n");
	} else {
		printf("Test validate_secret valid Failed\n");
	}

	result = validate_secret("invalid0");
	if (result != false) {
		printf("Test validate_secret invalid0 Passed\n");
	} else {
		printf("Test validate_secret invalid0 Failed\n");
	}
}

void test_string_contains_character() {
	bool result; 
	const char* strtest = "Professor Alvaro";

	if(!string_contains_character(strtest, 'z')) {
		printf("Test string_contains_character z Passed\n");
	} else {
		printf("Test string_contains_character z Failed\n");
	}

	if (string_contains_character(strtest, 'v')) {
		printf("Test string_contains_character v Passed\n");
	} else {
		printf("Test string_contains_character v Failed\n");
	}

	if (!string_contains_character(strtest, 'p')) {
		printf("Test string_contains_character p Passed\n");
	} else {
		printf("Test string_contains_character p Failed\n");
	}
}

void test_read_letter() {
	char c = read_letter();
	printf("Letter read: '%c'\n", c);
}




int main() {
	test_is_lowercase_letter();
	test_validate_secret();
	test_string_contains_character(); 
	test_read_letter(); 

	return 0;
}

