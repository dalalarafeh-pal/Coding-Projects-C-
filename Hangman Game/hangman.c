#include "hangman_helpers.h"

void win(char *secret) {
	printf("You win! The secret phrase was: %s\n", secret);
}

void lose(char *secret) {
	printf("You lose! The secret phrase was: %s\n", secret);
}

void eliminate(char *alphabet_letters) {
	printf("\nEliminated: ");
	for (char i = 'a'; i <= 'z'; i++) {
		if (alphabet_letters[i - 'a'] == 2) {
			printf("%c", i);
		}
	}
	printf("\n");
}

int countGuessedLetters(const char *secret, const char *alphabet_letters) {
	int guessed_letters = 0;
	const char *punctuation = " -'";
	size_t secret_length = strlen(secret); 

	for (size_t i = 0; i < secret_length; i++) {
 		bool special_character = false;
		for (size_t j = 0; punctuation[j] != '\0'; j++) {
			if (secret[i] == punctuation[j]) {
				special_character = true;
				break;
			}
		}
	
		if (special_character || alphabet_letters[secret[i] - 'a'] == 1) {
			printf("%c", secret[i]);
			guessed_letters++;

		} else {
			printf("_");	
		}	
	}
	
	return guessed_letters; 
}

int main(int argc, char **argv) {
	if (argc == 2) {
		char secret[MAX_LENGTH];
		char alphabet_letters[26] = {0};
		int mistakes = 0;
		int guessed_letters;
		size_t secret_length = strlen(argv[1]);  
		char current_guess = '\0';
		bool guess; 


		if (validate_secret(argv[1])) {
			strcpy(secret, argv[1]);

			while(1) {
				printf("%s", CLEAR_SCREEN);
				printf("%s\n\n", arts[mistakes]);
				printf("    Phrase: ");

				guessed_letters = countGuessedLetters(secret, alphabet_letters);
				eliminate (alphabet_letters);

				if (mistakes == LOSING_MISTAKE) {
					lose(secret);
					break;
				}

				if (guessed_letters == (int) secret_length) {
					win(secret);
					break;
				}

				while(1) {
					current_guess = read_letter();
					if (is_lowercase_letter(current_guess) && alphabet_letters[current_guess - 'a'] == 0) {
						alphabet_letters[current_guess - 'a'] = 1;

						guess = string_contains_character(secret, current_guess);
						if (guess){
							alphabet_letters[current_guess - 'a'] = 1;
						} else {
							alphabet_letters[current_guess - 'a'] = 2;
							mistakes++;
						}
						break; 	
					}

				}
 
			}	
		} else {
			return 1;
		
		}

	} else {
		printf("wrong number of arguments\nusage: ./hangman <secret word or phrase>\nif the secret is multiple words, you must qoute it\n");
		return 1; 
	}
	return 0; 	

}

