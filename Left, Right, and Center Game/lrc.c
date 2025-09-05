#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

const Position die[6] = {
	DOT,
	DOT,
	DOT,
	LEFT,
	CENTER,
	RIGHT,
};

const char *player_name[] = {
	"Ada Lovelace",
	"Margaret Hamilton",
	"Katherine Johnson",
	"Joy Buolawmini",
	"Grace Hopper",
	"Adele Goldberg",
	"Annie Easley",
	"Jeannette Wing",
	"Mary Kenneth Keller",
	"Megan Smith"
};

int check_winner(int *chips, int num_players);
void print_winner(int winner);


int input_num_players(void){
//prompt the user to the number of players, scanning in their input from stdin
	int num_players = 3;
	printf("Number of players (3 to 10)?");
	int scanf_result = scanf("%d", &num_players);
	if (scanf_result < 1 || num_players < 3 || num_players > 10){
		fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
		num_players = 3; 
	}
	return num_players;
}


unsigned input_seed(void){
//prompt the user to input the random seed for this run of LRC 
	unsigned seed = 4823;
	printf("Random-number seed?");
	int scanf_result = scanf("%u", &seed);
	if (scanf_result < 1) {
		fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
		seed = 4823;
	}
	return seed;
}

void roll_dice(int num_rolls, Position *results) {
	for (int i = 0; i < num_rolls; i++) {
		int roll = rand() % 6;
		results[i] = die[roll];
	}
}

void pass_chip_to_right(int *chips, int currentPlayer, int num_players) {
	int rightPlayer = (currentPlayer -1 + num_players) % num_players;
	chips[currentPlayer]--;
	chips[rightPlayer]++;
}

void pass_chip_to_left(int *chips, int currentPlayer, int num_players) {
	int leftPlayer = (currentPlayer + 1) % num_players;
	chips[currentPlayer]--;
	chips[leftPlayer]++;
}

void add_chip_to_pot(int *chips, int *pot, int currentPlayer) {
	chips[currentPlayer]--;
	*pot += 1;
}

void game_loop(int num_players, unsigned seed) {
	int chips[num_players];
	int pot = 0;
	for (int i = 0; i < num_players; i++) {
		chips[i] = 3;
	}

	srand(seed);

	while (1) {
		for (int player = 0; player < num_players; player++) {
			if (chips[player] > 0) {
				printf("%s:", player_name[player]);

				int num_rolls;
				if(chips[player] > 3) {
					num_rolls = 3;
				} else {
					num_rolls = chips[player];
				}

				Position roll_results[num_rolls];
				roll_dice(num_rolls, roll_results);

				for (int i = 0; i < num_rolls; i++) {
					if (roll_results[i] == RIGHT) {
						pass_chip_to_right(chips, player, num_players);
					} else if (roll_results[i] == CENTER) {
						add_chip_to_pot(chips, &pot, player);
					} else if (roll_results[i] == LEFT) {
						pass_chip_to_left(chips, player, num_players);
					}
				}

				printf(" ends her turn with %d\n", chips[player]);
			}

			int winner = check_winner(chips, num_players);
			if (winner != -1) {
				print_winner(winner);
				return;
			}
		}
	}
}

int check_winner(int *chips, int num_players) {
	int players_with_chips = 0;
	int winner = -1;
	for (int i = 0; i < num_players; i++) {
		if (chips[i] > 0) {
			if (++players_with_chips > 1) {
				return -1;
			}
			winner = i;
		}
	}
	return winner;
}

void print_winner(int winner) {
	if (winner != -1) {
		printf("%s won!\n", player_name[winner]);
	}
}

int main() {
	int num_players = input_num_players();
	unsigned seed = input_seed();
	game_loop(num_players, seed);
	return 0;
}

