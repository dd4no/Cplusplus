/***************************/
/*       BLACKJACK         */
/*		------------	   */	
/*    Dave Defourneaux	   */
/***************************/


/////////// libraries /////////////////////
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


////////// functions ////////////////////
int card();																// random card generator
char suit();															// random suit generator
int player_turn(int value[], char letter[], char suitz[], int total);	// player routine
int dealer_turn(int value[], char letter[], char suitz[], int total);	// dealer routine
char face(int card);													// facecard chooser
void showcards(int value[], char face[], char suit[], int length);		// show cards


////////// main ////////////////////
void main()
{
	/***** initialize game environment *****/
	srand((unsigned)time(NULL));		// seed random number generator with new number
	int purse = 100;					// starting funds
	char another = 'Y';					// default answer to "play another?" is 'yes'
	int i = 0;							// initialize counter variable
	int	game = 1;							// initialize game counter


	cout << endl;
	for (i =0 ; i<10 ; i++) cout << suit();
	cout << "     *****  WELCOME TO THE BLACKJACK TABLE *****     ";
	for (i =0 ; i<10 ; i++) cout << suit();
	cout << endl << endl;
	cout << "			     House Rules:" << endl;
	cout << "		-----------------------------------------" << endl << endl;
	cout << "		     No Double-Down or Split Hands" << endl;
	cout << "		     Dealer Wins on Ties	" << endl;
	cout << "		     Dealer Hits on 16, Stays on 17" << endl << endl;
	cout << "		-----------------------------------------" << endl << endl;
	
	
	/***** main game loop *****/
	do
	{
		/***-- initialize a new hand --***/
		int bet = 0;							// set bet to zero
		i = 0;									// intitalize counter variable
		

		/*- player variables -*/
		int phand = 0;							// player hand value
		int pcard[10] = {NULL};					// 2 card hand array -card value
		char psuit[10] = {NULL};				// 2 card hand array -card suit
		char pface[10] = {NULL};				// place holder for face card characters
				
		/*- dealer variables -*/
		int dhand = 0;							// dealer hand value
		int dcard[10] = {NULL};					// 2 card hand array -card value
		char dsuit[10] = {NULL};				// 2 card hand array -card suit
		char dface[10] = {NULL};				// place holder for face card characters
		int dholev = 0;							// set dealer hole-card value to zero
		char dholes = NULL;						// set dealer hole-card suit to zero
		char dholef = NULL;						// set dealer hole-card facecard to zero


		/***-- place bet --***/
		if (game != 1) system("cls");
		if (game == 1) cout << "	YOU START WITH $" << purse << endl;
		else cout << endl << "	FUNDS :  $" << purse << endl;		// display funds
		game ++;
		cout << endl << "	How much would you like to wager?  $";				// enter bet
		cin >> bet;

		/***-- deal cards --***/
		for (i=0 ; i<2 ; i++)				// deal a two-card hand to player and dealer
		{
			
			/*- player hand -*/
			pcard[i] = card();					// load player card value array
			psuit[i] = suit();					// load player card suit array
			if (pcard[i] > 10)					// check for facecard
			{
				pface[i] = face(pcard[i]);		// call facecard chooser function if true
				pcard[i] = 10;					// assign facecard value of 10
			}
			else if (pcard[i] == 1) pface[i] = 'A';
			else pface[i] = 'x';
			phand += pcard[i];					// add card value to player hand value
		
             
			/*- dealer hand -*/
			dcard[i] = card();					// load dealer card value array
			dsuit[i] = suit();					// load dealer card suit array
			if (dcard[i] > 10)					// check for facecard
			{
				dface[i] = face(dcard[i]);		// call facecard chooser function if true
				dcard[i] = 10;					// assign facecard value of 10
			}
			else if (dcard[i] == 1) dface[i] = 'A';
			else dface[i] = 'x';
			dhand += dcard[i];					// add card value to dealer hand value
		
        }
		/***-- end deal cards --***/
		
		/***-- hide second dealer card --***/
		dholev = dcard[1];
		dholes = dsuit[1];
		dholef = dface[1];
		dcard[1] = 0;
		dsuit[1] = '?';
		dface[1] = '?';

				
		/***-- show initial hands --***/
		system("cls");
		cout << endl << "FUNDS: $" << purse << "		BET: $" << bet << endl << endl;
		cout << endl << "DEALER'S HAND:" << endl;
		showcards(dcard, dface, dsuit, i);
		cout << endl << endl << "YOUR HAND:" << endl;
		showcards(pcard, pface, psuit, i);
		cout << endl << endl;

		/***-- unhide dealer hole-card --***/
		dcard[1] = dholev;
		dsuit[1] = dholes;
		dface[1] = dholef;
		
		/***-- check for blackjack --***/
		
		/*- player hand -*/
		if ((phand == 21) && (dhand != 21))						// if player has 21 and 
		{													//	dealer does not
			printf("You have Blackjack!!. You win!!\n");	// display blackjack for player
			purse += (bet * 1.5);							// winnings equal bet plus half bet
			goto END;										// jump to end of hand
		}
		
		/*- dealer hand -*/
		if (dhand == 21)									// if dealer hand equals 21
		{
			printf("Dealer has Blackjack.  You lose!\n");	// display blackjack for dealer
			purse -= bet;									// subtract bet from funds
			goto END;										// jump to end of hand
		}

		/***-- call player routine --***/
		
		phand = player_turn(pcard, pface, psuit, phand);	// send player hand value and 
															//	return progressive value 
															//	after player turn	
		if (phand > 21)									// zero returned if busted so..
		{											
			purse -= bet;									//	deduct bet from funds
			cout << endl << "FUNDS: $" << purse << endl;
			goto END;										//  and jump to end of hand
		}
		
		/***-- call dealer routine --***/
		system("cls");
		dhand = dealer_turn(dcard, dface, dsuit, dhand);						// send dealer hand value and
															//	return progressive value
															//	after dealer turn
		if (dhand > 21)									// zero returned if busted so..
		{
			purse += bet;									//	add bet to funds
			cout << endl << "FUNDS: $" << purse << endl;
			goto END;										//  and jump to end of hand
		}
		
		/***-- compare hands --***/
		cout << endl << endl;
		cout << "--------------------------------------------------------------";
		
		cout << endl << "You have " << phand << "\tDealer has " << dhand << endl;
		if (phand > dhand)								// if player hand beats dealer hand
		{
			purse += bet;									// add bet to funds
			printf("YOU WIN!!!!!!\n");						// display notification
		}

		if (phand <= dhand)									// if dealer hand beats or ties
		{													//	player hand
			purse -= bet;									// deduct bet from funds 
			printf("\nYOU LOSE!!!!!!\n");					// display notification
		}
		cout << endl << endl << "FUNDS: $" << purse << endl;
END: 
		/***-- end of hand --***/	
		 
		/***-- loop to play again --***/
		printf("\nWould you like to play again?  ");		// ask question
		cin >> another;										// get answer
	
	}while ((toupper (another) != 'N');						// exit if 'no'
	/***** end main game loop *****/													
	system("cls");
	cout << endl << endl << endl << "Thanks for playing!  Come Again...." << endl << endl;
}



////////// card generator ////////////////////
int card()
{
	int c = rand()%12 + 1;			// random value from 1 to 13
	return c;
}


////////// suit generator ////////////////////
char suit()
{
	char s = rand()%3 + 3;			// random suit based on ascii codes
	return s;
}


////////// facecard chooser ////////////////////
char face(int card)
{
	char facecard = 'x';							// initialize facecard to null value
          switch(card)								// choose switch based on card value
                {
                case 11: facecard = 'J'; break;		// ll is a jack
                case 12: facecard = 'Q'; break;		// 12 is a queen
                case 13: facecard = 'K'; break;		// 13 is a king
                }
          return facecard;							// return character to main
}


////////// player routine ////////////////////
int player_turn(int value[], char letter[], char suitz[], int total)
{
	/***** hit or stay choice *****/
	char choice = 'S';												// default to 'stay'
	int cards = 2;
	cout << endl << "(H)it or (S)tay?";								// ask question
	cin >> choice;													// get answer
	
	/***** hit me loop *****/
	while (toupper(choice) == 'H')							// run loop while answer is 'hit'
	{
		value[cards] = card();								// draw a new card value
		if( value[cards] > 10 )								// check for face card
		{
			letter[cards] = face(value[cards]);				// if facecard call facecard chooser
			value[cards] = 10;								//	set value to 10
		}
		else if (value[cards] == 1) letter[cards] = 'A';
		else letter[cards] = 'x';							// else set facecard to 'x'
		suitz[cards] = suit();
		
		total += value[cards];								// cummulate hand total
		cards ++;											// increment loop count
		
		system("cls");										// clear screed
		cout << endl << "YOUR HAND:" << endl;				// show cards
		showcards(value, letter, suitz, cards);
		
		if( total > 21 )									// if hand totals more than 21
		{
			cout << endl << "You busted!!! You lose your bet!";		//	output message
			cout << endl;
			choice = 'S';									// change from 'hit' to 'stay'
			continue;										// exit loop
		}
		cout << endl << "(H)it or (S)tay?  ";				// ask question
		cin >> choice;										// get answer
	}

	return total;											// return hand value to main
}


////////// dealer routine ////////////////////
int dealer_turn(int value[], char letter[], char suitz[], int total)
{
	/***** dealer hits on 16 or less *****/
	int cards = 2;

	//cout << endl << "DEALER'S HAND:" << endl;
	//showcards(value, letter, suitz, cards);
	
	if ( total <= 16 )																			
	{
		while (total < 17)											// exit if over 17
		{
			value[cards] = card();								// draw a new card value
			if( value[cards] > 10 )								// check for face card
			{
				letter[cards] = face(value[cards]);				// if facecard call facecard chooser
				value[cards] = 10;								//	set value to 10
			}
			else if (value[cards] == 1) letter[cards] = 'A';
			else letter[cards] = 'x';							// else set facecard to 'x'
			suitz[cards] = suit();
			
			total += value[cards];										// add value to hand
			cards ++;
			
		}
		cout << endl << "DEALER'S HAND:" << endl;
		showcards(value, letter, suitz, cards);

		if (total <=21)												// if not over 21
		{
			cout << endl << " Dealer stands on " << total << endl;	//	dealer stands
		}
		
		else if (total > 21)										// if over 21 
		{
			cout << endl << "Dealer busted!!! You win !!!" << endl;// busted
		}
	}
	
	/***** dealer stays on 17 or more *****/
	else if ( total >= 17 )
	{
		cout << endl << " Dealer stands on " << total << endl;		// display notification
	}
		
	return total;													// return hand value to main
}


////////// show cards ////////////////////
void showcards(int value[], char face[], char suit [], int length)
{
	int total = 0;
		
	for (int i=0 ; i<length ; i++) printf(" -----  ");
	cout << endl;
	for (i=0 ; i<length ; i++) printf("|     | ");
	cout << endl;
	for (i=0 ; i<length ; i++)
	{
		if (face[i] != 'x') printf("| %c%c  | ", face[i], suit[i]);
		else if (value[i] == 10) printf("| %i%c | ", value[i], suit[i]);
		else if (value[i] == 0) printf("| ?%c  | ", suit[i]);
		else printf("| %i%c  | ", value[i], suit[i]);
	}
	cout << endl;
	for (i=0 ; i<length ; i++) printf("|     | ");
	cout << endl;
	for (i=0 ; i<length ; i++) printf(" -----  ");
	cout << endl;
	
	for (i=0 ; i<length ; i++) total += value[i];
	
	cout << endl;
	if( value[1] == 0) printf(" Dealer shows : %i", total);
	else printf(" Hand Totals : %i", total);
	cout << endl;
		

}