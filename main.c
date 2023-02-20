#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "safeinput.h" 


void main(){

    bool playAgain = true;
    bool stillGuesing;
    int playerGuess; 
    int nrOfGuesses;

    srand(time(NULL));

    while(playAgain){

        int randomNumber = rand() % 100 + 1;

        printf("TEST: %d\n", randomNumber); //TEST LINE

        stillGuesing = true;
        nrOfGuesses = 1;

        printf("GUESS A NUMBER BETWEEN 1 - 100\n");
        
        while(stillGuesing){

            printf("GUESS%d: ",nrOfGuesses);

            while(GetInputInt("", &playerGuess) == false){

                printf("You can only enter digits TRY AGAIN:\n");
                printf("GUESS%d: ",nrOfGuesses);
            }
                        
            if(playerGuess > randomNumber){

                printf("The number is smaller\n");
                nrOfGuesses++;

            }
            else if(playerGuess < randomNumber){
                
                printf("The number is bigger\n");
                nrOfGuesses++;
            }
            else if (playerGuess == randomNumber){

                printf("RIGHT!! You guessed the right number in %d tries\n", nrOfGuesses);
                stillGuesing = false;
            }
        }

        while(true){
           
            char input[10];
            GetInput("Do you want to play again (YES/NO)? ", input, sizeof(input));

                if(strcmp("NO", input) == 0 ){
                    printf("Thank you for playing!");
                    playAgain = false;
                    break;
                }

                else if(strcmp("YES", input) == 0 ){
                    playAgain = true;
                    break;
                }
                else
                    printf("Yes or no please ");
        }

    }
    
}