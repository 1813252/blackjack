#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#define N_CARDSET 1
#define N_MAX_USER		5
#define N_MAX_CARDHOLD		10

int CardTray[N_CARDSET*52];
int n_user;	
int dollar[N_MAX_USER];
int bet[N_MAX_USER];
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD]; 
int cardSum[N_MAX_USER];
int gameEnd=1 ;
int cardcnt;
int round=1;

void offerCards(void);
int configUser(void);
int mixCardTray(void);
int pullCard(void); //get one card from the tray
int getCardNum(int cardnum);
void printCard(int cardnum);
int betDollar(void);

int my_turn();
int dealer_turn();
int player_turn(int player);

void printUserCardStatus(int user, int cardcnt); 
int calcStepResult(int user, int cardcnt);
void play();
int checkWinner();
void printCardInitialStatus();

int main(void) {
		
	int i;
	int sel;
	
	srand((unsigned)time(NULL));
	
	configUser();
		
	mixCardTray();
	
	for (i=0;i<n_user;i++)
	{		
		dollar[i]=50;
	}
	
	int gameEnd=1;
	

	do{
	
	play();
	
		
	for (i=0;i<n_user;i++)
	{
		gameEnd*=dollar[i];
	}
	
	round++;
	
	} while (gameEnd!=0);
	
	return 0;
}




void play(){
	
	printf("\n--------------------\n-------------Round %d------------------\n------",round);
	betDollar();
	offerCards();
	
	printCardInitialStatus();
	
	printf("\n-------------GAME START--------------\n");
	
	int my_sum;
	
	my_sum = my_turn();

	int player=1;
	
	
	int player_sum[player];
		
	for (player=1;player<n_user;player++)
	{	
		printf("\n-----player%d turn!------\n",player);
		printUserCardStatus (player,2);
	
		player_sum[player]=player_turn(player);

	
	}
	

	int dealer_sum;
	
	dealer_sum = dealer_turn();
	
	
	//result 
	printf("\n______________Round %d Result________________\n",round);
	
	
	
	printf("\n---->Your result :   ");
	if (calcStepResult(0,2)==21)
	{
		printf("BLACK JACK WIN!");
		dollar[0]+=2*bet[0];
		printf("----->$%d",dollar[0]);
	}
	else if (my_sum==21)
	{	
		printf("You Win!\n");
		printf("(Sum : 21)");
		dollar[0]+=bet[0];
		printf("----->$%d",dollar[0]);
	}

	else if(my_sum>21)
		{
			printf("You Lose!");
			printf("(Sum : %d)",my_sum);
			dollar[0]-=bet[0];
			printf("----->$%d",dollar[0]);
		}
		
		else if (dealer_sum>21)//burst가 아니고 blackjack도 아닌경우  
		{
			printf("You Win!"); 
			printf("(Sum : %d)",my_sum);
			dollar[0]+=bet[0];
			printf("------->%d",dollar[0]);
		}
		
		else if (my_sum<21 && dealer_sum>my_sum)
		{
			printf("You Lose!");
			dollar[0]-=bet[0];
			printf("(Sum : %d)",my_sum);
			printf("------->%d",dollar[0]);
		}
			
		else
	   	{   printf("You Win!");
			printf("(Sum : %d)",my_sum);
			dollar[0]+=bet[0];
			printf("----->$%d",dollar[0]);
		}
			
	
	

	for (player=1;player<n_user;player++){
		
	printf("\n---->player %d result : ",player);
		
	if (calcStepResult(player,2)==21)
	{
		printf("BLACK JACK WIN!");
		dollar[player]+=2*bet[player];
		printf("----->$%d",dollar[player]);
		
	}
	else if (player_sum[player]==21)
	{	
		printf(" Win!");
		printf("(Sum : 21)");
		dollar[player]+=bet[player];
		printf("----->$%d",dollar[player]);
	}

	else if(player_sum[player]>21)
		{
			printf(" Lose!");
			printf("(Sum : %d)",player_sum[player]);
			dollar[player]-=bet[player];
			printf("----->$%d",dollar[player]);
		}
		
		else if (dealer_sum>21)//burst가 아니고 blackjack도 아닌경우  
		{
			printf(" Win!"); 
			printf("(Sum : %d)",player_sum[player]);
			dollar[player]+=bet[player];
			printf("----->$%d",dollar[player]);
		}
		
		else if ( dealer_sum>player_sum[player])
		{
			printf(" Lose!");
			printf("(Sum : %d)",player_sum[player]);
			dollar[player]-=bet[player];
			printf("----->$%d",dollar[0]);
		}
			
		else
	   	{ 
		    printf(" Win!");
		    printf("(Sum : %d)",player_sum[player]);
		   	dollar[player]+=bet[player];
		   	printf("----->$%d",dollar[player]);
		}
	}
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
		printf(" Hart%s","A");
		
		else if (2<=cardnum%13 && cardnum%13<=10)//2~10
		printf(" Hart%d",cardnum%13);
		
		else if (cardnum%13==11) 
		printf(" Hart%s","J");
		
		else if (cardnum%13==12)
		printf(" Hart%s","Q");
	
		else 
		printf(" Hart%s","K");		
	
	}		
	
	if (cardnum/13==1)
	{
		if (cardnum%13==1)
		printf(" Dia%s","A");
		
		else if (2<=cardnum%13 && cardnum%13<=10)
		printf(" Dia%d",cardnum%13);
		
		else if (cardnum%13==11) 
		printf(" Dia%s","J");
		 
		else if (cardnum%13==12)
		printf(" Dia%s","Q");
	
		else 
		printf(" Dia%s","K");		
		
	}
	
	if (cardnum/13==2)
	{
		
		if (cardnum%13==1)
		printf(" Spade%s","A");
		
		else if (2<=cardnum%13 && cardnum%13<=10)
		printf(" Spade%d",cardnum%13);
		
		else if (cardnum%13==11) 
		printf(" Spade%s","J");
		
		else if (cardnum%13==12)
		printf(" Spade%s","Q");
	
		else 
		printf(" Spade%s","K");
	}
	
	if (cardnum/13==3)
	{
		if (cardnum%13==1)
		printf(" Club%s","A");
			
		else if(2<=cardnum%13 && cardnum%13<=10)
		printf(" Club%d",cardnum%13);
		
		else if (cardnum%13==11) 
		printf(" Club%s","J");
		
		else if (cardnum%13==12)
		printf(" Club%s","Q");
	
		else 
		printf(" Club%s\n","K");
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
	
	printf("\n");	
	printf(" ------- BETTING STEP -------- ");
	printf("Your betting : ");
	scanf("%d",&bet[0]);
	printf("You bets $%d (out of $%d)\n",bet[0],dollar[0]);
	int i;
	
	for (i=1;i<n_user;i++)
	{
		bet[i]= (rand()%dollar[i])+1;
		printf("player %d bets $%d (out of $%d)\n",i,bet[i],dollar[i]);
			
	}
	
	return bet[n_user],dollar[n_user];
	
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
		printCard(cardhold[0][1]);
		printf("\n");
		
		for (i=1;i<n_user;i++){
			
			printf("\n");
			printf("->player %d\n",i);
			printCard(cardhold[i][0]);
			printCard(cardhold[i][1]);
			printf("->player %d cardsum : %d\n",i,calcStepResult(i,2));
			printf("\n");
		}
		printf("\n---server  :  X ");
		printCard(cardhold[n_user][1]);		
			
	 
}


int calcStepResult(int user, int cardcnt){
		
	int cardSum[N_MAX_USER];
	
	int i,sum=0;
	
	  for  (i=0;i<cardcnt;i++){
	
	 sum+=getCardNum(cardhold[user][i]); //일단 A는 11로 고정  
	}
	cardSum[user]=sum;
	
	 return cardSum[user];
	 	
}

//>>> my turn! -------------
   // card : DIA10 HRTJack       ::: Action? (0 - go, 1 - stay) :
int my_turn(void){ 

	printf("\n---------------my Turn-----------------\n");
	printUserCardStatus (0,2);
	printf("Your Card Sum : %d\n",calcStepResult(0,2));
	
	if (calcStepResult(0,2)==21)
	{
		printf("BLACKJACK!\n");
		return calcStepResult(0,2);
	}
	
	else {
	int i=0;
	int cardcnt=2;
	
	for (i=0; i<8; i++)
	{
		int action;
		
		printf("\n <GO=1, STAY=0> \n");
		
		do{
			scanf("%d",&action);
		} while (action!=1 && action!=0);
		
	
		if (action==1)
		{
			printf("GO!\n");
			cardhold[0][i+2]=pullCard();
			cardcnt++;
			printUserCardStatus(0,cardcnt);
		
			
			if (calcStepResult(0,cardcnt) > 21)
			{
				printf("Sum of player's cards now:%d\n\n",calcStepResult(0,cardcnt));
				printf("BURST!\n");
				return calcStepResult(0,cardcnt);
			}
			else if (calcStepResult(0,cardcnt) == 21)
			{
				printf("Sum of player's cards now:%d\n\n",calcStepResult(0,cardcnt));
				return calcStepResult(0,cardcnt);
			}		
			else 
		
			printf("Sum of player's cards now:%d\n\n",calcStepResult(0,cardcnt));
			
		}
		else if (action==0)
		{
			printf("STAY!\n");
			printf("Sum of player's cards now:%d\n\n",calcStepResult(0,cardcnt));
			return calcStepResult(0,cardcnt);
		
		}
	}
}
	
}
int player_turn(int player){
	
	int i=0;
	int cardcnt=2;
	
	if (calcStepResult(player,2)==21)
	{
		printf("BLACKJACK!\n");
		return calcStepResult(player,2);
	}
	
	else {
	for (i=0; i<8; i++)
	{
	
		if (calcStepResult(player,cardcnt)<17)
		{
			printf("GO!\n");
			cardhold[player][i+2]=pullCard();
			cardcnt++;
			printUserCardStatus(player,cardcnt);
		
		 if (calcStepResult(player,cardcnt) > 21)
			{
				printf("Sum of player %d's cards now:%d\n\n",player,calcStepResult(player,cardcnt));
				printf("BURST!\n");
				return calcStepResult(player,cardcnt);
			}
			else if (calcStepResult(player,cardcnt) == 21)
			{
				printf("Sum of player %d's cards now:%d\n\n",player,calcStepResult(player,cardcnt));
				return calcStepResult(player,cardcnt);
			}	
			
			else
			
			
			printf("Sum of player %d's cards now:%d\n\n",player,calcStepResult(player,cardcnt));	
			
	}
		else if (calcStepResult(player,cardcnt)>=17) //action==0
		{	
			printf("STAY!\n");

			printf("Sum of player %d's cards now:%d\n\n",player,calcStepResult(player,cardcnt));
			return calcStepResult(player,cardcnt);
		}
	}
  }
}

int dealer_turn(){
	
	
	int i=0;
	int cardcnt=2;
	
	printf("-------Dealer Turn!-------\n");
	printUserCardStatus(n_user,cardcnt);
	
	
	if (calcStepResult(n_user,2)==21)
	{
		printf("BLACKJACK!\n");
		return calcStepResult(n_user,2);
	}
	
	else {
		
	for (i=0; i<8; i++)
	{
	
		if (calcStepResult(n_user,cardcnt)<17)
		{
			printf("GO!\n");
			cardhold[n_user][i+2]=pullCard();
			cardcnt++;
		
		 if (calcStepResult(n_user,cardcnt) > 21)
			{
				printf("\n :::Sum of dealer's cards now:%d\n\n",calcStepResult(n_user,cardcnt));
				printf("BURST!\n");
				return calcStepResult(n_user,cardcnt);
			}
			else if (calcStepResult(n_user,cardcnt) == 21)
			{
				printf("\n :::Sum of dealer's cards now:%d\n\n",calcStepResult(n_user,cardcnt));
				return calcStepResult(n_user,cardcnt);
			}	
			
			else
			
			printUserCardStatus(n_user,cardcnt);	
			
	}
		else if (calcStepResult(n_user,cardcnt)>=17) //action==0
		{	
			printf("STAY!");
			printf("\n :::Sum of dealer's cards now : %d",calcStepResult(n_user,cardcnt));
			return calcStepResult(n_user,cardcnt);
		}
	}
  }
}

void printUserCardStatus(int user, int cardcnt) { //처음 2장 받을때? 

	int i;
	
	printf(" \n-> card : \n");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}

//cardhold[n_user][0];

