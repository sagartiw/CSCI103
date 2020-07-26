/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Sagar Tiwari
 * USC email: sagartiw@usc.edu
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[]){
    for(int i = 51; i > 0; i--){
        int j = rand()%(i+1);
        int temp = cards[j];
        cards[j] = cards[i];
        cards[i] = temp;
    }
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, S, D, C
 */
void printCard(int id){
    cout << type[id%13] << "-";
    
    if(0 <= id && id <= 12){
        cout << suit[0];
    }
    else if(13 <= id && id <= 25){
        cout << suit[1];
    }
    else if(26 <= id && id <= 38){
        cout << suit[2];
    }
    else{
        cout << suit[3];
    }
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
    return value[id%13];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    for(int i = 0; i < numCards; i++){
        printCard(hand[i]);
        cout << " ";
    }
    cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    int sum = 0;
    int acecounter = 0;
    for(int i = 0; i < numCards; i++){
        sum += cardValue(hand[i]);
        if(cardValue(hand[i]) == 11){
            acecounter++;
        }
        if(sum > 21 && acecounter > 0){
            sum -= 10;
            acecounter--;
        }
    }
    return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
    bool gameon = 1;
    char hitorstay;
    char yesorno;
    int pcounter;
    int dcounter;
    int deck;
    int secondcard;
    while(gameon){
        for(int i = 0; i < 52; i++){
            cards[i] = i;
        }
        shuffle(cards);
        phand[0] = cards[0];
        dhand[0] = cards[1];
        phand[1] = cards[2];
        dhand[1] = cards[3];
        deck = 4;
        pcounter = 2;
        dcounter = 2;
        secondcard = dhand[1];

        cout << "Dealer: ? ";
        printCard(secondcard);
        cout << endl;
        cout << "Player: ";
        printHand(phand, 2);

        if(getBestScore(phand, 2) != 21){
            cout << "Type 'h' to hit and 's' to stay:" << endl;
            while(getBestScore(phand, pcounter) < 21){
                cin >> hitorstay;

                if(hitorstay == 'h'){
                    phand[pcounter] = cards[deck];
                    pcounter++;
                    deck++;
                }
                else if(hitorstay == 's'){
                    break;
                }
                else{
                    return 2;
                }
                
                cout << "Player: ";
                printHand(phand, pcounter);

                if(getBestScore(phand, pcounter) < 21){
                    cout << "Type 'h' to hit and 's' to stay:" << endl;
                }
                else if(getBestScore(phand, pcounter) == 21){
                    break;
                }
                else{
                    cout << "Player busts" << endl;
                    cout << "Lose " << getBestScore(phand, pcounter) << " " 
                    	 << getBestScore(dhand, dcounter) << endl << endl;
                    cout << "Play again? [y/n]" << endl;
                    goto gameover;
                }
            }
        }

    	while(getBestScore(dhand, dcounter) < 17){
	        dhand[dcounter] = cards[deck];
	        dcounter++;
	        deck++;
	    }

	    if(getBestScore(phand, pcounter) > getBestScore(dhand, dcounter) &&
	    	getBestScore(phand, pcounter) <= 21){
	    	cout << "Dealer: ";
	    	printHand(dhand, dcounter);
	    	cout << "Win " << getBestScore(phand, pcounter) << " " <<
	    		 getBestScore(dhand, dcounter) << endl << endl;
	    	cout << "Play again? [y/n]" << endl;
	    }
	    else if(getBestScore(dhand, dcounter) > getBestScore(phand, pcounter)){
	    	if(getBestScore(dhand, dcounter) > 21){
	    		cout << "Dealer: ";
	    		printHand(dhand, dcounter);
	    		cout << "Dealer busts" << endl;
	    		cout << "Win " << getBestScore(phand, pcounter) << " " <<
	    			 getBestScore(dhand, dcounter) << endl << endl;
	    		cout << "Play again? [y/n]" << endl;
	    	}
	    	else{
	    		cout << "Dealer: ";
	    		printHand(dhand, dcounter);
	    		cout << "Lose " << getBestScore(phand, pcounter) << " "
                    	 << getBestScore(dhand, dcounter) << endl << endl;
                cout << "Play again? [y/n]" << endl;
	    	}
	    }
	    else{
	    	cout << "Dealer: ";
	    	printHand(dhand, dcounter);
	    	cout << endl;
	    	cout << "Tie " << getBestScore(phand, pcounter) << " " <<
	    		 getBestScore(dhand, dcounter) << endl << endl;
	    	cout << "Play again? [y/n]" << endl;
	    }

        gameover:
        cin >> yesorno;
        if(yesorno == 'y'){
        	continue;
        }
        else{
        	gameon = 0;
        	break;
        }
    }
  return 0;
}