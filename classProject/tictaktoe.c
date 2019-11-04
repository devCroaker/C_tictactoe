#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *fp;

void greet(void);
void printMenu(void);
int getSelection(void);
void clearBuff(char string[]);
void newGame(int players);
char getPlayerSymbol(int players);
void printBoard(char board[][3]);
void readPlayerMove(int players, int first, char currentPlayer, char board[][3]);
void calcComputerMove(char currentPlayer, char board[][3]);
char checkWinners(char board[][3]);

int main(void) {

	if (!(fp = fopen("csis.txt", "w"))) {
		printf("Could not open the file");
		return 0;
	}

	int selection = 0;

	greet();
	do {
		printMenu();
		selection = getSelection();
		if (selection != 4) {
			newGame(selection);
		}
	} while (selection != 4);

	fclose(fp);
	return 0;
}

void greet(void) {
	printf("Hello! Welcome to my game! Are you ready to play tic-tac-toe?\n\n");
	fprintf(fp, "Hello! Welcome to my game! Are you ready to play tic-tac-toe?\n\n");
}

void printMenu(void) {
	printf("%27s\n", "TIC-TAC-TOE GAME MENU");
	fprintf(fp, "%27s\n", "TIC-TAC-TOE GAME MENU");
	printf("%35s\n", "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
	fprintf(fp, "%35s\n", "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
	printf(" 1) Start A Single Player Game\n");
	fprintf(fp, " 1) Start A Single Player Game\n");
	printf(" 2) Start A Two Player Game\n");
	fprintf(fp, " 2) Start A Two Player Game\n");
	printf(" 3) Start Computer vs Computer Game\n");
	fprintf(fp, " 3) Start Computer vs Computer Game\n");
	printf(" 4) Exit Program\n\n");
	fprintf(fp, " 4) Exit Program\n\n");
}

int getSelection(void) {

	char selection[2], invalid = 0;

	do {
		if (invalid) {
			printf("\nPlease enter a valid selection!\n");
			fprintf(fp, "\nPlease enter a valid selection!\n");
		}

		printf("Please make a selction (1-4)\n");
		fprintf(fp, "Please make a selction (1-4)\n");
		fgets(selection,2,stdin);
		clearBuff(selection);
		invalid = 1;

	} while (selection[0] != '1' && selection[0] != '2' && selection[0] != '3' && selection[0] != '4');
	int retSelection = selection[0] - '0';

	return retSelection;

}

void clearBuff(char string[]) {
	char *p;
	if (p = strchr(string, '\n')) {//check exist newline
		*p = 0;
	}
	else {
		scanf("%*[^\n]"); scanf("%*c");//clear upto newline
	}
}

void newGame(int players) {

	char player1, player2, win;
	int first = (rand() % 2 == 0);
	char board[3][3] = {
		{ '\0', '\0', '\0' },
		{ '\0', '\0', '\0' },
		{ '\0', '\0', '\0' }
	};

	if (players != 3) {
		player1 = getPlayerSymbol(players);
		player2 = (player1 == 'X') ? 'O' : 'X';

		printf("\nRandomly determining who will go first...\n");
		fprintf(fp, "\nRandomly determining who will go first...\n");
		printf("%s won the coin toss and will go first\n\n", (first) ? (players == 1) ? "You have" : "Player 1 has" : (players == 1) ? "The computer has" : "Player 2 has");
		fprintf(fp, "%s won the coin toss and will go first\n\n", (first) ? (players == 1) ? "You have" : "Player 1 has" : (players == 1) ? "The computer has" : "Player 2 has");

	} else {
		player1 = 'X'; player2 = 'O';
		printf("\nRandomly determining who will go first...\n");
		fprintf(fp, "\nRandomly determining who will go first...\n");
		printf("%c-computer has won the coin toss and will go first\n\n", (first) ? player1 : player2);
		fprintf(fp, "%c-computer has won the coin toss and will go first\n\n", (first) ? player1 : player2);

	}

	do {

		if (first) {
			if (players == 3) {
				calcComputerMove(player1, board);
			} else {
				readPlayerMove(players, first, player1, board);
			}
		} else {
			if (players == 2) {
				readPlayerMove(players, first, player2, board);
			} else {
				calcComputerMove(player2, board);
			}
		}

		first = !first;

	} while (!(win = checkWinners(board)));

	printBoard(board);
	if (win == 'D') {
		printf("The game has ended in a draw!\n\n\n");
		fprintf(fp, "The game has ended in a draw!\n\n\n");
		return;
	}
	printf("%s the winner!\n\n\n", (players == 1) ? (win == player1) ? "You are" : "The Computer is" : (win == player1) ? "Player 1 is" : "Player 2 is");
	fprintf(fp, "%s the winner!\n\n\n", (players == 1) ? (win == player1) ? "You are" : "The Computer is" : (win == player1) ? "Player 1 is" : "Player 2 is");

}

char getPlayerSymbol(int players) {

	char symbol[2], invalid = 0;
	do {
		if (invalid) {
			printf("\nPlease enter a valid selection!\n");
			fprintf(fp, "\nPlease enter a valid selection!\n");
		}

		printf("\n%slease choose to play as either Xs or Os (X or O):\n", (players == 2) ? "Player 1 p" : "P");
		fprintf(fp, "\n%slease choose to play as either Xs or Os (X or O):\n", (players == 2) ? "Player 1 p" : "P");
		fgets(symbol,2,stdin);
		clearBuff(symbol);
		symbol[0] = toupper(symbol[0]);
		invalid = 1;

	} while (symbol[0] != 'X' && symbol[0] != 'O');

	printf("Great! %s will play as %cs\n", (players == 2) ? "Player 2" : "The Computer", (symbol[0] == 'X') ? 'O' : 'X');
	fprintf(fp, "Great! %s will play as %cs\n", (players == 2) ? "Player 2" : "The Computer", (symbol[0] == 'X') ? 'O' : 'X');

	return symbol[0];

}

void printBoard(char board[][3]) {

	printf("   A   B   C\n");
	fprintf(fp, "   A   B   C\n");
	for (int i = 0; i < 3; i++) {
		printf("%d  %1c | %1c | %1c \n", (i+1), board[i][0], board[i][1], board[i][2]);
		fprintf(fp, "%d  %1c | %1c | %1c \n", (i + 1), board[i][0], board[i][1], board[i][2]);
		printf("%s", (i != 2) ? "  ------------\n" : "\n");
		fprintf(fp, "%s", (i != 2) ? "  ------------\n" : "\n");
	}

}

void readPlayerMove(int players, int first, char currentPlayer, char board[][3]) {

	char playerMove[3], valid = 1;

	printBoard(board);

	do {
		printf("%slease input your move based on its two digit coordinate (ex. A1, B2, C3):\n", (players == 1) ? "P" : (first) ? "Player 1 p" : "Player 2 p");
		fprintf(fp, "%slease input your move based on its two digit coordinate (ex. A1, B2, C3):\n", (players == 1) ? "P" : (first) ? "Player 1 p" : "Player 2 p");
		fgets(playerMove,3,stdin);
		clearBuff(playerMove);
		playerMove[0] = toupper(playerMove[0]);

		if (
			!( (playerMove[0] == 'A' || playerMove[0] == 'B' || playerMove[0] == 'C') && (playerMove[1] == '1' || playerMove[1] == '2' || playerMove[1] == '3') )
		) {
			printf("Invalid move! Please input a valid move:\n");
			fprintf(fp, "Invalid move! Please input a valid move:\n");
			valid = 0;
			continue;
		}
		putchar('\n');
		fprintf(fp, "%c", '\n');

		int row = (playerMove[0] == 'A') ? 0 : (playerMove[0] == 'B') ? 1 : 2;
		int column = (playerMove[1] - 1) - '0';
		if (board[column][row] != '\0') {
			printf("Move taken! Please input a valid move:\n");
			fprintf(fp, "Move taken! Please input a valid move:\n");
			valid = 0;
			continue;
		}

		board[column][row] = currentPlayer;
		valid = 1;

	} while (!valid);

}

void calcComputerMove(char player, char board[][3]) {

	int moveI = 4, moveJ = 4, emptys = 0;
	char otherPlayer = (player == 'X') ? 'O' : 'X';

	printBoard(board);
	printf("Calculating the %c-computers move...\n\n", player);
	fprintf(fp, "Calculating the %c-computers move...\n\n", player);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '\0') {
				// Check for winning moves
				board[i][j] = player;
				if (checkWinners(board) == player) {
					return;
				} else {
					// Check for losing moves, continue to look for winners
					board[i][j] = otherPlayer;
					if (checkWinners(board) == otherPlayer) {
						moveI = i; moveJ = j;
					}
					board[i][j] = '\0';
					emptys++;
				}
			}
		}
	}

	// if no winners make the losing move
	if (moveI < 4 && moveJ < 4) {
		board[moveI][moveJ] = player;
		return;
	}

	// if this is the second move and the middle is empty take it
	if (board[1][1] == '\0' && emptys == 8) {
		board[1][1] = player;
		return;
	}

	// no winner, no looser, no middle, make a random move
	int play = (rand() % emptys) + 1, num = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '\0') {
				num++;
				if (num == play) {
					board[i][j] = player;
				}
			}
		}
	}

}

char checkWinners(char board[][3]) {

	int i;
	char symbol;

	// check rows
	for (i = 0; i < 3; i++) {
		symbol = board[i][0];
		if (symbol == board[i][1] && symbol == board[i][2] && symbol != '\0') {
			return symbol;
		}
	}

	// check columns
	for (i = 0; i < 3; i++) {
		symbol = board[0][i];
		if (symbol == board[1][i] && symbol == board[2][i] && symbol != '\0') {
			return symbol;
		}
	}

	// check diag
	symbol = board[0][0];
	if (symbol == board[1][1] && symbol == board[2][2] && symbol != '\0') {
		return symbol;
	}

	// check antidiag
	symbol = board[0][2];
	if (symbol == board[1][1] && symbol == board[2][0] && symbol != '\0') {
		return symbol;
	}

	// Check Draw
	int num = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != '\0') {
				num++;
			}
		}
	}

	if (num == 9) {
		return 'D';
	}

	return 0;
}
