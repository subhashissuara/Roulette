/*
	Made by Subhashis Suara
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

/*
	38 squares
	0 and 00 - green - lose
	18 - red - randomly ordered
	18 - black - randomly ordered
*/

bool flag = true; // Keep track of while loop exit condition
bool green; // To keep track of green squares
int result_num = 0; // Number rolled by rand()
float winningAmount = 0; // Stores the winning amount for each bet
int lostPlayers[10]; // Keep track of lost players and avoid them from playing
int lostplayers_cnt = 0; // To keep track of index of lostPlayers array

// slno is serial number of player
int choose(float players[], int slno);
int single(float players[], int slno, float bet);
int redorblack(float players[], int slno, float bet);
int oddoreven(float players[], int slno, float bet);
int lowerorhigher(float players[], int slno, float bet); 
int randfor38();
bool randfor2(); 
// output when the square choosen is green
int displayGreen(int slno);

int main(){
	bool last = false;
	int size = 0;
	float startMoney = 0;
	printf("Enter the number of players: \n");
	scanf("%d", &size);
	printf("\nEnter initial cash for everyone in dollars($): \n");
	scanf("%f", &startMoney);
	float players[size];

	for(int cnt = 0; cnt < size; cnt++){
		players[cnt] = startMoney;
	}

	printf("\nAll players have been give %f$ to start with! \n", startMoney);

	srand(time(NULL));
	while(flag){
		bool check; // To skip lost players
		bool win = false;
		for(int i = 1; i <= size; i++){
			for(int j = 0; j < 10; j++){
				if(i == lostPlayers[j]){
					check = true;
					if((size - lostplayers_cnt) == 1)
						win = true;
					if((size - lostplayers_cnt) == 0){
						printf("All players are out from the game! No one won!\n");
						flag = false;
					}
				if(check)
					break;
				}
				else
					check = false;
			}
			if(win){
				for(int i = 1; i <= size; i++){
					last = true;
					for(int j = 0; j < 10; j++){
						if(i == lostPlayers[j]){
							last = false;
							break;
						}
					}
					if(last){
						printf("\nPlayer %d won the game as all other players have been eliminated!\n", i);
						flag = false;
						break;
					}
				}
				
			}
			else
			{
				if(check)
					continue;
				else
					choose(players, i - 1);
			}
			if(last || check)
				break;
		}
	}
	return 0;
}

// Menu for choosing the bet
int choose(float players[], int slno){
	int choice = 0;
	float bet = 0;
	printf("\nChoose your bet player %d: \n", slno + 1);
	printf("1. A single red or black square.\n");
	printf("2. A color, either red or black.\n");
	printf("3. An odd or even number.\n");
	printf("4. The lower 18 or the higher 18 numbers.\n");
	printf("\nEnter the serial number:\n");
	scanf("%d", &choice);

	printf("Enter the amount of bet: \n");
	scanf("%f", &bet);
	if(bet > players[slno]){
		printf("\nYou bet more than your balance!\n");
		bet = 0;
		choice = 0;
		choose(players, slno);
	}
	else if(bet < 0){
		printf("\nYou bet in negetive numbers!\n");
		bet = 0;
		choice = 0;
		choose(players, slno);
	}
	else
	{
		switch (choice)
		{
		case 1:
			single(players, slno, bet);
			break;

		case 2:
			redorblack(players, slno, bet);
			break;

		case 3:
			oddoreven(players, slno, bet);
			break;

		case 4:
			lowerorhigher(players, slno, bet);
			break;
		
		default:
			printf("Invalid choice!\n");
			choose(players, slno);
			break;
		}
	}
}

/*
	1 - Won
	2 - Lost
*/
bool randfor2(){
	int chosen = ((rand()) % (2 - 1 + 1) + 1);
	if(chosen == 1)
		return true;
	else
		return false;
}

/*
	1 - 36 numbers - red or black - Won
	37 - 0 - green - Lost
	38 - 00 - green - Lost
*/
int randfor38(){
	int chosen = ((rand()) % (38 - 1 + 1) + 1);
	return chosen;		
}

int displayGreen(int slno){
	printf("\nThe color rolled was green!\n");
	lostPlayers[lostplayers_cnt] = slno + 1;
	lostplayers_cnt++;
	printf("Player %d is out from the game!\n", slno + 1);
}

int single(float players[], int slno, float bet){
	int choice = 0;
	winningAmount = bet + 35*bet;
	result_num = randfor38();
	printf("\nEnter a number between 1 - 36 to bet on:\n");
	scanf("%d", &choice);

	if (choice > 36 || choice < 1)
	{
		printf("Invalid choice! Choose between 1 - 36!\n");
		choice = 0;
		single(players, slno, bet);
	}
	
	if(result_num > 36){
		green = true;
		displayGreen(slno);
		return 0;
	}

	if (choice == result_num)
	{
		printf("\nPlayer %d won the bet!\n", slno + 1);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Bet amount: %f$\n", bet);
		printf("Winning amount: %f$\n", winningAmount);
		players[slno] += winningAmount;
		printf("Total balance: %f$\n", players[slno]);
		
	}
	
	else
	{
		printf("\nPlayer %d lost the bet!\n", slno + 1);
		printf("The number rolled was: %d!\n", result_num);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Losing amount: %f$\n", bet);
		players[slno] -= bet;
		printf("Total balance: %f$\n", players[slno]);
		if(players[slno] <= 0){
			printf("\nPlayer %d has gone bankrupt!\n", slno + 1);
			lostPlayers[lostplayers_cnt] = slno + 1;
			lostplayers_cnt++;
			printf("Player %d is out from the game!\n", slno + 1);
		}
	}
	
}

int redorblack(float players[], int slno, float bet){
	int choice = 0;
	winningAmount = bet*2;
	printf("\nChoose your bet: \n");
	printf("1. Red \n");
	printf("2. Black \n");
	printf("\nEnter the serial number:\n");
	scanf("%d", &choice);

	if (choice > 2 || choice < 1)
	{
		printf("Invalid choice! Choose 1 or 2!\n");
		choice = 0;
		redorblack(players, slno, bet);
	}

	if(result_num > 36){
		green = true;
		displayGreen(slno);
		return 0;
	}

	if(choice == 1){
		char choice_text_1[] = "black";
		if (randfor2()){
		printf("\nPlayer %d won the bet!\n", slno + 1);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Bet amount: %f$\n", bet);
		printf("Winning amount: %f$\n", winningAmount);
		players[slno] += winningAmount;
		printf("Total balance: %f$\n", players[slno]);
		
		}
	
		else{
			printf("\nPlayer %d lost the bet!\n", slno + 1);
			printf("The color rolled was %s!\n", choice_text_1);
			printf("Initial amount: %f$\n", players[slno]);
			printf("Losing amount: %f$\n", bet);
			players[slno] -= bet;
			printf("Total balance: %f$\n", players[slno]);
			if(players[slno] <= 0){
				printf("\nPlayer %d has gone bankrupt!\n", slno + 1);
				lostPlayers[lostplayers_cnt] = slno + 1;
				lostplayers_cnt++;
				printf("Player %d is out from the game!\n", slno + 1);
			}
		}
	}
	else{
		char choice_text_2[] = "red";

		if (randfor2())
		{
		printf("\nPlayer %d won the bet!\n", slno + 1);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Bet amount: %f$\n", bet);
		printf("Winning amount: %f$\n", winningAmount);
		players[slno] += winningAmount;
		printf("Total balance: %f$\n", players[slno]);
		
		}
	
	else
		{
		printf("\nPlayer %d lost the bet!\n", slno + 1);
		printf("The color rolled was %s!\n", choice_text_2);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Losing amount: %f$\n", bet);
		players[slno] -= bet;
		printf("Total balance: %f$\n", players[slno]);
		if(players[slno] <= 0){
			printf("\nPlayer %d has gone bankrupt!\n", slno + 1);
			lostPlayers[lostplayers_cnt] = slno + 1;
			lostplayers_cnt++;
			printf("Player %d is out from the game!\n", slno + 1);
			}
		}
	}
}

int oddoreven(float players[], int slno, float bet){
	int choice = 0;
	winningAmount = bet*2;
	result_num = randfor38();
	printf("\nChoose your bet: \n");
	printf("1. Odd \n");
	printf("2. Even \n");
	printf("\nEnter the serial number:\n");
	scanf("%d", &choice);

	if (choice > 2 || choice < 1)
	{
		printf("Invalid choice! Choose 1 or 2!\n");
		choice = 0;
		oddoreven(players, slno, bet);
	}

	if(result_num > 36){
		green = true;
		displayGreen(slno);
		return 0;
	}

	if(choice == 2)
		choice = 0;

	if (result_num%2 == choice)
	{
		printf("\nPlayer %d won the bet!\n", slno + 1);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Bet amount: %f$\n", bet);
		printf("Winning amount: %f$\n", winningAmount);
		players[slno] += winningAmount;
		printf("Total balance: %f$\n", players[slno]);
		
	}
	
	else
	{
		printf("\nPlayer %d lost the bet!\n", slno + 1);
		printf("The number rolled was: %d!\n", result_num);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Losing amount: %f$\n", bet);
		players[slno] -= bet;
		printf("Total balance: %f$\n", players[slno]);
		if(players[slno] <= 0){
			printf("\nPlayer %d has gone bankrupt!\n", slno + 1);
			lostPlayers[lostplayers_cnt] = slno + 1;
			lostplayers_cnt++;
			printf("Player %d is out from the game!\n", slno + 1);
		}
	}
}

int lowerorhigher(float players[], int slno, float bet){
	int choice = 0;
	winningAmount = bet*2;
	result_num = randfor38();
	printf("\nChoose your bet: \n");
	printf("1. Number lower than 18 \n");
	printf("2. Number higher than 18 \n");
	printf("\nEnter the serial number:\n");
	scanf("%d", &choice);

	if (choice > 2 || choice < 1)
	{
		printf("Invalid choice! Choose 1 or 2!\n");
		choice = 0;
		lowerorhigher(players, slno, bet);
	}

	if(result_num > 36){
		green = true;
		displayGreen(slno);
		return 0;
	}

	if(choice == 1){
		char choice_text_1[] = "higher than 18";

		if (result_num < 18){
		printf("\nPlayer %d won the bet!\n", slno + 1);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Bet amount: %f$\n", bet);
		printf("Winning amount: %f$\n", winningAmount);
		players[slno] += winningAmount;
		printf("Total balance: %f$\n", players[slno]);
		
		}
	
		else{
			printf("\nPlayer %d lost the bet!\n", slno + 1);
			printf("The number rolled was %d which is %s!\n", result_num, choice_text_1);
			printf("Initial amount: %f$\n", players[slno]);
			printf("Losing amount: %f$\n", bet);
			players[slno] -= bet;
			printf("Total balance: %f$\n", players[slno]);
			if(players[slno] <= 0){
				printf("\nPlayer %d has gone bankrupt!\n", slno + 1);
				lostPlayers[lostplayers_cnt] = slno + 1;
				lostplayers_cnt++;
				printf("Player %d is out from the game!\n", slno + 1);
				}
			
			}
	}
		
	else{
		char choice_text_2[] = "lower than 18";

		if (result_num > 18){
		printf("\nPlayer %d won the bet!\n", slno + 1);
		printf("Initial amount: %f$\n", players[slno]);
		printf("Bet amount: %f$\n", bet);
		printf("Winning amount: %f$\n", winningAmount);
		players[slno] += winningAmount;
		printf("Total balance: %f$\n", players[slno]);
		
		}
	
		else{
			printf("\nPlayer %d lost the bet!\n", slno + 1);
			printf("The number rolled was %d which is %s!\n", result_num, choice_text_2);
			printf("Initial amount: %f$\n", players[slno]);
			printf("Losing amount: %f$\n", bet);
			players[slno] -= bet;
			printf("Total balance: %f$\n", players[slno]);
			if(players[slno] <= 0){
				printf("\nPlayer %d has gone bankrupt!\n", slno + 1);
				lostPlayers[lostplayers_cnt] = slno + 1;
				lostplayers_cnt++;
				printf("Player %d is out from the game!\n", slno + 1);
				}
			
			}
	}
}
