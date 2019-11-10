#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#define N_CARDSET 1
#define N_MAX_USER		5
#define N_MAX_CARDHOLD		10

int CardTray[N_CARDSET*52];
int n_user;	
int dollar[N_MAX_USER];	//dollars that each player has dollar[0]_나,dollar[1],dollar[2]...
int bet[N_MAX_USER];
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; //여기까지함 

int cardSum[N_MAX_USER];					//sum of the cards
int gameEnd = 0;

void offerCards(void);
int configUser(void);
int mixCardTray(void);
int pullCard(void); //get one card from the tray
int getCardNum(int cardnum);
void printCard(int cardnum);
int betDollar(void);
void printCardInitialStatus(void); //여기까지함 

int getAction(void);
void printUserCardStatus(int user, int cardcnt);
int calcStepResult();
int checkResult();
int checkWinner();

	
int main(int argc, char *argv[]) {
		
	int i;
	
	srand((unsigned)time(NULL));
	
	configUser();
		
	mixCardTray();
	
	betDollar();
	offerCards();
	
	printCardInitialStatus();
	printf("\n------------------ GAME start --------------------------\n");
	

	return 0;
}

int pullCard(void){ //카드 한장씩 꺼내기 
//cardtray[0],cardtray[1]..순서대로 출력  
	
	static int j=0;
	
	j++;	
		
	return CardTray[j];
	
}


int mixCardTray(void){
	
int i,j;

int  one_cardset[52] ={1,2,3,4,5,6,7,8,9,10,11,12,13,         //hart 0-12
					   14,15,16,17,18,19,20,21,22,23,24,25,26,//club 13-25
					   27,28,29,30,31,32,33,34,45,36,37,38,39, //dia 26-38
					   40,41,42,43,44,45,46,47,48,49,50,51,52};  //spade 39-51
		  		
	for (j=0;j<N_CARDSET;j++){
		
		for (i=0; i<52; i++)
		
		CardTray[(52*j)+i]= one_cardset[i]; 
		
	}
	
int k,rnd,temp;

	for (k=0;k<51;k++){   //k는 전역변수 처리를 해야하는지? 
		
		rnd = rand()%(k+1);
		temp = CardTray[k];
		CardTray[k]=CardTray[rnd];
		CardTray[rnd]=temp;
	}	
	
	printf("card is mixed and put into the tray");
	
}


void printCard(int cardnum) {
	
	if (cardnum/13==0)
	
	{	
		if (cardnum%13==1)
		printf("Hart%s","A");
		
		else if (2<=cardnum%13 && cardnum%13<=10)//2~10
		printf("Hart%d\n",cardnum%13);
		
		else if (cardnum%13==11) 
		printf("Hart%s\n","J");
		
		else if (cardnum%13==12)
		printf("Hart%s\n","Q");
	
		else 
		printf("Hart%s\n","K");		
	
	}		
	
	if (cardnum/13==1)
	{
		if (cardnum%13==1)
		printf("Dia%s","A");
		
		else if (2<=cardnum%13 && cardnum%13<=10)
		printf("Dia%d\n",cardnum%13);
		
		else if (cardnum%13==11) 
		printf("Dia%s\n","J");
		
		else if (cardnum%13==12)
		printf("Dia%s\n","Q");
	
		else 
		printf("Dia%s\n","K");		
		
	}
	
	if (cardnum/13==2)
	{
		
		if (cardnum%13==1)
		printf("Spade%s","A");
		
		else if (2<=cardnum%13 && cardnum%13<=10)
		printf("Spade%d\n",cardnum%13);
		
		else if (cardnum%13==11) 
		printf("Spade%s\n","J");
		
		else if (cardnum%13==12)
		printf("Spade%s\n","Q");
	
		else 
		printf("Spade%s\n","K");
	}
	
	if (cardnum/13==3)
	{
		if (cardnum%13==1)
		printf("Club%s","A");
			
		else if(2<=cardnum%13 && cardnum%13<=10)
		printf("Club%d\n",cardnum%13);
		
		else if (cardnum%13==11) 
		printf("Club%s\n","J");
		
		else if (cardnum%13==12)
		printf("Club%s\n","Q");
	
		else 
		printf("Club%s\n","K");
	}
	
	
}

	
int getCardNum(int cardnum) {
		
	int value;
	switch (cardnum%13){
		
		case 1:
		value=11;
		break;
		
		case 2:
		value=2;
		break;
		
		case 3:
		value=3;
		break;
		
		case 4:
		value=4;
		break;
		
		case 5:
		value=5;
		break;
		
		case 6:
		value=6;
		break;
		
		case 7:
		value=7;
		break;
		
		case 8:
		value=8;
		break;
		
		case 9:
		value=9;
		break;
		
		case 10:
		value=10;
		break;
		
		case 11:
		value=10;
		break;
		
		case 12:
		value=10;
		break;
		
		case 0:
		value=10;
		break;
	}
		
	return value;
		
}

int configUser(void){
	
	printf("input the number of player (MAX5):  ");
	scanf("%d",&n_user);
	
 //5보다 크면 다시 입력받도록 해야함 
}

int betDollar(void){
		
	int bet[N_MAX_USER]; //6칸 배열 배당 
	
	
	printf("\n");	
	printf(" ------- BETTING STEP -------- ");
	
	printf("your betting : ");
	scanf("%d",&bet[0]);
	int i;
	
	for (i=1;i<n_user;i++)
	{
		bet[i]= rand()%50;
		printf("player %d bets $%d (out of $50)\n",i,bet[i]);
			
	}
	
}

void offerCards(void) {
	
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}


void printCardInitialStatus(void) {
		
		int i;
		printf("---------card offering---------");
		printf("\n");
		printf("-> me : ");
		printCard(cardhold[0][0]);
		printCard(cardhold[1][0]);
		printf("\n");
		
		for (i=0;i<n_user-1;i++){
			
			printf("\n");
			printf("->player %d\n",i+1);
			printCard(cardhold[i][0]);
			printCard(cardhold[i][1]);
			printf("\n");
		}		
			
	
}

//>>> my turn! -------------
   // card : DIA10 HRTJack       ::: Action? (0 - go, others - stay) :
   	
int getAction(void){
	
	printf("\n >>> my turn !---------\n");

	}
	
	



//해야할것 _  5명 이상 안받기, 2판 이상부터할떄 자본금? 















