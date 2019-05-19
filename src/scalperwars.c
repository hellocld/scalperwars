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
void printHeader(char str[]);
void printBar();

void mainMenu();
void gameLoop();
void printLocale(int id);
void printTicketStats(int id);
void printPlayerStats();

void playerAction();

void buy();
void sell();
void travel();

void randomEvent();

int getActionInput();

void defaultPrices();
void init();
int dumbTix[3];

int gameRunning = 1;

int day = 0;
int currentLocale = 0;
int tixHeld[1];
int cash = 500;
int score = 0;

int main()
{
	/* Initialization stuff */
	init();
	defaultPrices();
	
	printTitle(" SCALPER WARS ");
	mainMenu();
	while(gameRunning) {
		gameLoop();
	}
	printTitle("GAME OVER");
	printf("Your score was %d\n\n", cash);

}

void defaultPrices()
{
	dumbTix[N_BUFFALO] = 20;
	dumbTix[S_BUFFALO] = 30;
	dumbTix[ORCHARD]   = 35;

}

void init()
{
		tixHeld[0] = 0;
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

void printHeader(char str[])
{
	printf("********** %s *********\n\n", str);
}

void printBar()
{
	for(int i = 0; i < 80; ++i)
		printf("*");
	printf("\n");
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
	printBar();
	if(day > 14) {
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

void printPlayerStats()
{
	printBar();
	printf("\tCash:\t$%d\n", cash);
	printf("\tTix:\t%d\n", tixHeld[0]);
}

void playerAction()
{
	printPlayerStats();
	printf("What choo gonna do?\n");
	printf("\t1) Buy\n\t2) Sell\n\t3) Jet\n\n? ");
	int c = getActionInput();
	if(c < 1 || c > 3) {
			printf("What?? You can't do that %d.\n", c);
			playerAction();
	}
	switch(c) {
		case 1:
			printf("Buy!\n");
			buy();
			break;
		case 2:
			printf("Sell!\n");
			sell();
			break;
		case 3:
			printf("Jet!\n");
			travel();
			break;
		default:
			printf("What?? I don't understand %c\n", c);
			playerAction();
			break;
	}
}

void travel()
{
	printf("Where to?\n");
	printf("\t1) North Buffalo\n");
	printf("\t2) South Buffalo\n");
	printf("\t3) Orchard Park\n");
	int l = getActionInput();
	if(l < 1 || l > 3) {
		printf("Where?? Try again buddy.\n");
		travel();
	}
	currentLocale = l - 1;
	++day;
	randomEvent();
}

void buy()
{
	printf("How many? ");
	char s[MAXSTRING];
	char c;
	int i = 0;
	for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
		if(!isdigit(c)) {
			printf("That's not a number, yo!\n");
			buy();
		}
		s[i] = c;
	}
	s[i] = '\0';
	int num = atoi(s);
	int cost = num * dumbTix[currentLocale];
	if(cost > cash) {
		printf("You can't afford $%d worth of tickets!\n", cost);
		return;
	}
	cash -= cost;
	tixHeld[0] += num;
}

void sell()
{
	printf("How many? ");
	char s[MAXSTRING];
	char c;
	int i;
	for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
		if(!isdigit(c)) {
			printf("That's not a number, yo!\n");
			sell();
		}
		s[i] = c;
	}
	s[i] = '\0';
	int num = atoi(s);
	if(num > tixHeld[0]) {
		printf("You don't have that many tickets to sell, dog!\n");
		return;
	}
	tixHeld[0] -= num;
	cash += num * dumbTix[currentLocale];
}

int getActionInput()
{
		int c;
		int i = -1;
		while((c = getchar()) != EOF && c != '\n') {
			if(isdigit(c))
				i = c - '0';
		}
		return i;
}

void randomEvent()
{
	/* This probably should go somewhere smarter */
	defaultPrices();

	float r = rand() / (float)RAND_MAX;

	if(r > 0.7) {
		r = (rand() / (float)RAND_MAX) * 4;
		switch((int)r) {
			case 0:
					/* Tickets skyrocket */
					r = rand() / (float)RAND_MAX;
					dumbTix[N_BUFFALO] += r * 15;
					dumbTix[S_BUFFALO] += r * 15;
					dumbTix[ORCHARD] += r * 15;
					printf("Ticket prices just jumped!\n");
					break;
			case 1:
					/* Tickets plummet */
					r = rand() / (float)RAND_MAX;
					dumbTix[N_BUFFALO] -= r * 5;
					dumbTix[S_BUFFALO] -= r * 5;
					dumbTix[ORCHARD] -= r * 5;
					printf("Ticket prices just dropped!\n");
					break;
			case 2:
					/* Get mugged */
					r = rand() / (float)RAND_MAX;
					if(r >= 0.5) {
							cash -= (rand() / (float)RAND_MAX) * 20;
							if(cash < 0)
									cash = 0;
							printf("Some dude just mugged you on the bus!!\n");
					} else {
							tixHeld[0] -= (rand()/(float)RAND_MAX) * 10;
							if(tixHeld[0] < 0)
									tixHeld[0] = 0;
							printf("Somebody lifted some tickets off you on the bus! Bummer!\n");
					}
					break;
			case 3:
					/* Score free tickets */
					break;
			default:
					break;
		}
	}
}
