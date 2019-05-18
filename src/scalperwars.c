/* 
 * SCALPER WARS
 *
 * A game created for BGSjamXIV
 * Inspired by the classic DOS game "Drug Wars"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
void printTicketStats(int id);
void playerAction();

int dumbTix[3];

int gameRunning = 1;

int day = 0;
int currentLocale = 0;
int score = 0;

int main()
{
	/* Initialization stuff */
	dumbTix[N_BUFFALO] 	= 20;
	dumbTix[S_BUFFALO] 	= 30;
	dumbTix[ORCHARD]	= 35;
	
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
	++day;
	if(day > 30) {
		gameRunning = 0;
		return;
	}
	// Print locale info
	printf("WELCOME TO ");
	printLocale(currentLocale);
	printf("It's day %d of 30\n\n", day);
	printTicketStats(currentLocale);
	// Select Action
	playerAction();
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

void printTicketStats(int locationID)
{
	printf("Current ticket rates:\n");
	printf("\t- Dumb tickets: $%d\n\n", dumbTix[locationID]);
}

void playerAction()
{
	printf("What choo gonna do?\n");
	printf("\t1) Buy\n\t2) Sell\n\t3) Jet\n\n? ");
	char c;
	while((c = getchar()) != EOF && c != '\n') {
		if(!isdigit(c)) 
			printf("What? Enter a number 1-3, yo\n? ");
		switch(c) {
			case '1':
				printf("Buy!\n");
				break;
			case '2':
				printf("Sell!\n");
				break;
			case '3':
				printf("Jet!\n");
				break;
			default:
				printf("What?? I don't understand %c\n", c);
				playerAction();
				break;
		}
	}
}
