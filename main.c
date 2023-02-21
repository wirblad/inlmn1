#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "safeinput.h"


struct player{

    char name[50];
    char dateAndTime[50];
    int completeNrOfGuess;

};

struct player list[4];

int meny();
void play();
void checklowscore(int nrOfGuesses);
void saveTolowscore(int nrOfGuesses, int placeInLowScore);
void showLowScore();
void saveToFile();
void loadFile();

void main(){

    loadFile();
    while(true){

        int menyChoice = meny();
    
        if(menyChoice == 1){
            play();  
        }
        else if(menyChoice == 2)
            break;
        else if(menyChoice == 3){
            loadFile();
            showLowScore();
        }
    }
}

int meny(){

    printf("\n1. PLAY AGAIN\n2. END\n3. LOWSCORE\n\n");
    int menyChoice;

    while(GetInputInt("", &menyChoice) == false || menyChoice > 3 || menyChoice < 1 ){

                printf("PLEASE CHOOSE A NUMBER 1-3 TRY AGAIN:\n");
                printf("1. PLAY AGAIN\n2. END\n3. LOWSCORE\n");   
            }
    return menyChoice;
}

void play(){

    bool stillGuesing;
    int playerGuess; 
    int nrOfGuesses;

    srand(time(NULL));

    int randomNumber = rand() % 100 + 1;

    //printf("TEST: %d\n", randomNumber); //--------TEST LINE -------------

    stillGuesing = true;
    nrOfGuesses = 1;

    printf("GUESS A NUMBER BETWEEN 1 - 100\n");
        
        while(stillGuesing){

            printf("GUESS%d: ",nrOfGuesses);

            while(GetInputInt("", &playerGuess) == false || playerGuess < 1 || playerGuess > 100){

                printf("You can only enter digits and guesses between 1 - 100 TRY AGAIN:\n");
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
                checklowscore(nrOfGuesses);  
            } 
        }    
}

void checklowscore(int nrOfGuesses){
 
    for( int i = 0 ; i <= 4; i++){

        if ( nrOfGuesses > list[i].completeNrOfGuess){
        
            printf("\nCONGRATZ!!! U MADE IT TO THE LOW SCORE!!!\n");
            saveTolowscore(nrOfGuesses, i);
            break;
        }   
    }
}

void saveTolowscore(int nrOfGuesses, int placeInLowScore){

    time_t rawtime;
    struct tm *info;
    char buffer[50];

    time( &rawtime );
    info = localtime( &rawtime );
    strftime(buffer,80,"%x - %I:%M%p", info);

    struct player player;
    
    player.completeNrOfGuess = nrOfGuesses;
    strcpy(player.dateAndTime, buffer);
    GetInput("Enter player name: ", player.name, sizeof(player.name));
    //shift position in lowscore
    for(int i = 4 ; i > placeInLowScore ; i--){
        list[i] = list[i-1]; 
    }
    list[placeInLowScore] = player;
    printf("\nINFO ABOUT THIS ROUND: \n------PLAYER: %s\n------GUESSES: %d\n------DATE: %s\n\n", player.name, player.completeNrOfGuess, player.dateAndTime);
    saveToFile();
}

void showLowScore(){

    for( int i = 0 ; i <= 4; i++){
        printf("POS %d\n------PLAYER: %s\n------GUESSES: %d\n------DATE: %s\n", i+1 , list[i].name, list[i].completeNrOfGuess, list[i].dateAndTime);
    }
}

void saveToFile(){

FILE *outfile;
     
// open file for writing
outfile = fopen ("lowscore.dat", "w");

if (outfile == NULL){
    fprintf(stderr, "\nError opened file\n");
    exit (1);
}

fwrite (&list[0], sizeof(struct player), 1, outfile);
fwrite (&list[1], sizeof(struct player), 1, outfile);
fwrite (&list[2], sizeof(struct player), 1, outfile);
fwrite (&list[3], sizeof(struct player), 1, outfile);
fwrite (&list[4], sizeof(struct player), 1, outfile);
     
if(fwrite != 0)
    printf("contents to file written successfully !\n");
else
    printf("error writing file !\n");
 
// close file
fclose (outfile);

}

void loadFile(){

    FILE *infile;
     
    // Open person.dat for reading
    infile = fopen ("lowscore.dat", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }
     
    // read file contents
    
    fread (&list[0], sizeof(struct player), 1, infile);
    fread (&list[1], sizeof(struct player), 1, infile);
    fread (&list[2], sizeof(struct player), 1, infile);
    fread (&list[3], sizeof(struct player), 1, infile);
    fread (&list[4], sizeof(struct player), 1, infile);
      
    // close file
    fclose (infile);
}
