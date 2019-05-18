/* 
 * SCALPER WARS
 *
 * A game created for BGSjamXIV
 * Inspired by the classic DOS game "Drug Wars"
 *
 */

#include <stdio.h>

#define MAXSTRING 10000

/* Locales */
#define N_BUFFALO	0
#define S_BUFFALO	1
#define ORCHARD 	2


void printTitle(char str[]);
//void printHeader(char str[]);

void mainMenu();
void gameLoop();
void printLocale(int id);

int gameRunning = 1;

int currentLocale = 0;
int score = 0;

int main()
{
	printTitle(" SCALPER WARS ");
	mainMenu();
	while(gameRunning) {
			gameLoop();
	}
	printTitle("GAME OVER");
	printf("Your score was %d\n\n", score);

}

void printTitle(char str[])
{
	int l = 0;
	while(str[++l] != '\0')
		;
	for(int i = 0; i < l + 4; ++i)
		printf("*");
	printf("\n* %s *\n", str);
	for(int i = 0; i < l + 4; ++i)
		printf("*");
	printf("\n\n");
}

void mainMenu()
{
	printf("Welcome to Scalper Wars!\n");
	printf("Do you need directions? (y/N) ");
	char help;
	while((help = getchar()) != EOF && help != '\n')
		if(help == 'y' || help == 'Y')
			printf("\nScalper Wars is a dumb game. Nuff said.\n\n");
}

void gameLoop()
{
	// Print locale info
	printf("WELCOME TO ");
	printLocale(currentLocale);
	gameRunning = 0;
	// Select Action
	// Buy/Sell/Travel
}

void printLocale(int locationID)
{
	switch(locationID) {
			case N_BUFFALO:
					printf("NORTH BUFFALO");
					break;
			case S_BUFFALO:
					printf("SOUTH BUFFALO");
					break;
			case ORCHARD:
					printf("ORCHARD PARK");
					break;
			default:
					printf("ERROR: Unknown locale %d\n", locationID);
					break;
	}
	printf("\n\n");
}
