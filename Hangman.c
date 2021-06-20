/*
    Name: Nicholas Evelyn
    USI: 1035375
    Course: CSE1201
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#define STRMAX 100 
#define SIZE 15 

/*
C does not have native support for returning strings in a similar manner to Python, Java or other object oriented languages. 
To get around this, I created a String structure which a function can return. Data stored in the custom string structure can be accessed 
through the 'data' member of the structure. Similar behavior can be achieved using pointers, but in my opinion, it is easier to read the code 
and follow the logic behind it using this method. One advantage of this approach is that it allows the code to be more modular since some 
text-processing logic can be deligated to dedicated functions.
*/
struct String {
    char data[STRMAX];
};

// The play function will contain the core logic of our hangman game.
void play(struct String);

// getMysteryWord() returns a random word from a list of words.
struct String getMysteryWord();

// hideWord() replaces text in a string with underscores, effectively hiding it.
struct String hideWord(struct String);

// uncoverValid() determines if a letter entered by the player is contained in the secret word. 
// If it is, then the underscores in that hidden word are replaced with the correctly guessed letter
struct String uncoverValid(struct String, struct String, char);

// search() loops through a string and determines if the string contains a character or not
bool search(struct String, char);

// Prints the stick-figure to the screen.
void printHangman(int);

int main(void) {

    bool running = true; // control whether to run the game or not

    char choice;

    struct String randomWord = getMysteryWord(); // generate a random word for the player to guess

    // pass the random word to the main game function. With this set-up, the game will always run at least once
    play(randomWord);

    while (running) {
        // Prompt the player if they want to play again or not
        printf("\nPlay again? (y/n): "); 

        fflush(stdin); // clear the input stream of garbage data
        scanf("%c", &choice);

        // if the user wants to play again, generate a new random word and activate the play() function
        if (choice == 'y') {
        	system("cls"); // refresh the screen so old content won't be displayed
            randomWord = getMysteryWord();
            play(randomWord);
        }

        // If the user doesn't want to play again, set running to false to break out of the game loop
        else if (choice == 'n') {
            running = false;
            system("cls");
            printf("\nThanks for playing. Bye :)");
            break;
        }

        // If the player has not chosen 'y' or 'n', tell them they must choose either 'y' or 'n' then continue back to the start of the loop. 
		//The program will keep asking the player for their choice until they enter either a 'y' or 'n' 
        else {
            printf("\nYou can only choose 'y' or 'n'");
            continue;
        }

    }
    return 0;
}

void play(struct String str) {
	// The play() function accepts a randomly generated secret word and hides it with the hideWord() function
    // All the contents of the randomly generated word will be replaced with underscores and stored in the hiddenWord variable.
    struct String hiddenWord = hideWord(str);
    int turns = 6; // Player has 6 turns to guess the correct answer
    bool guessed = false; // Determines whether the player correctly guessed the word or not
    bool found; // Determines if the letter the player entered is contained in the secret word
    bool repeated; // Determines whether a player already guess a particular letter
    char guess[STRMAX]; // The player's guess will be accepted as a character array


    printf("\nLet's play hangman!\n");
    printHangman(turns); // print the initial state of the hangman figure

    // While the player has not guessed the word and has not run out of turns
    while (!guessed && turns > 0) {
        
        // Print the hidden word and prompt the user to guess it
        printf("\n\nI am thinking of the word: %s", hiddenWord.data);
        printf("\nThe word is %d characters long", strlen(hiddenWord.data));

        printf("\nPlease enter a letter or word: ");
        fflush(stdin);
        scanf("%s", &guess);

        // if the length of the user's guess is 1 character, then that means they have entered a letter
        if (strlen(guess) == 1) {

            // search the mystery word to see if it contains the guessed letter or not
            found = search(str, guess[0]);

            // search the hidden word to see if it contains the guessed letter or not. 
			// If it does then that means the player has guessed this leter already
            repeated = search(hiddenWord, guess[0]);
            
            // If the player's guess is not in the mystery word then that means their guess was wrong, and they lose a turn
            if (!found) {
                printf("\nSorry, %s is not a letter in the secret word", guess);
                turns--;
            }
            
            // If the player's guess was already in the hidden word then they lose a turn
            else if (repeated) {
            	printf("\nYou already guessed %s!", guess);
            	turns--;
			}

            // If the player's guess was found and not repeated then execute the code in the else block
            else {
                printf("\nGood job! %s is a letter in the secret word!", guess);

                // replace the underscores in the hidden word with the correctly guessed letter
                hiddenWord = uncoverValid(str, hiddenWord, guess[0]);

                // once the underscores in hiddenWord have been replaced with the correct letters, we will check if it matches the mystery word. 
				// If it does then we set guessed to true meaning the player has won
                if (strcmp(hiddenWord.data, str.data) == 0) {
                    guessed = true;
                }
            }
        }

        // If the length of the player's guess is greater than 1 then that means the player entered an entire word
        else if (strlen(guess) > 1) {

            // Check if the word that the player guessed matches the mystery word. If it doesn't then the user loses a turn
            if (strcmp(str.data, guess) != 0) {
                printf("\nSorry, %s is not the secret word", guess);
                turns--;
            }
            
            // If the player's guess matches the mystery word then they have guessed the word correctly, and we can set guessed to true
            else {
                guessed = true; 
                printf("\nGreat guess!");
            }
        }

        // If the user's guess is invalid, print an error message
        else {
            printf("\nNot a valid guess");
        }
		
		sleep(1); // wait one second
		
		system("cls"); // clear the screen
		
		/*
        Print the figure that corresponds to the current turn. Example, if the user is on turn 6, then a certain hangman figure should be displayed.
        Since the printHangman() function relies on the current turn, and turn only gets decremented when the player makes an incorrect guess,
        this means that the hangman figure will only change if the player makes an incorrect guess. Otherwise, the same figure will be printed 
		over and over again.
        */
        printHangman(turns);

    }

    // If the user guessed the word, print a victory message
    if (guessed) printf("\nYou got it! The word I was thinking of was %s!", str.data);

    // Otherwise, the user has lost the game
    else printf("\nSorry, you lost :( The word I was thinking of was %s!", str.data);

}

struct String getMysteryWord() {

    struct String str;

    // Sync the random function to our computer's internal clock so we get a different random value each time the program runs
    srand(time(NULL));

    char randomWord[STRMAX]; // This array will hold the randomly generated word

    // 2D array holding the words we want the hangman game to use
    char strArray[SIZE][STRMAX] = {"wombat", "baboon", "badger", "jaguar", "beaver", "camel", "cat", "shark", 
	"llama","moose", "whale", "ferret", "seal", "parrot", "skunk"};

    /*
    Generate a random index between 0 and 14
    Note that the array has 15 elements and array indexes are from 0 to size of array minus 1).
    So to get numbers from 0 to size of the array, we generate a random number and
    find the modulus of it using the size of the array.
    */
    int randomIndex = rand() % SIZE;

    // Copy the value stored at randomIndex to the 'data' member of the String structure
    strcpy(str.data, strArray[randomIndex]);

    // Return the String structure which will now contain a random word in its 'data' member
    return str;
}

struct String hideWord(struct String inputStr) {
	
	int x;

    struct String str;

    // Get the length of the data member of the inputStr structure. 
    int N = strlen(inputStr.data);

    // This variable will contain the hidden word. This means that all the characters of the input string will be replaced with underscores
    char hiddenWord[N];
	
	/*
    loop from 0 to N, where N is the length of the data member of the inputStr structure.
    Add an underscore to the hidden word array until hidden word has the same length of the data member of the inputStr structure. 
	Hence, if the myster word has 5 letters, the hidden word will have 5 underscores correponding to each letter.
	*/
    for (x = 0; x < N; x++) {
        hiddenWord[x] = '_';
    }
	
    /*
	hiddenWord has an empty index at the end. We can add a null terminator here to indicate the end of the character array.
	If we don't do this, then we will encounter issues since the program won't know when the character array is supposed to end
    */
    hiddenWord[N] = '\0';
	
	// Copy the value in hiddeWord to the data member of the str structure
    strcpy(str.data, hiddenWord);
	
	// Return str structure
    return str;
}

bool search(struct String str, char key) {
	int x = 0;
	
    bool valueFound = false;
	
	// Loop from 0 to the length of the String data member
	// If the value at a given index is equal to the key, and the key isn't an underscore, then flip valueFound to true
	// We need to exclude underscores from our comparison or else it will return a false positive if we pass into the
	// function a word that contains underscores and an underscore character.
    for (x = 0; x < strlen(str.data); x++) {
        if (str.data[x] == key && key != '_') {
            valueFound = true;
            break;
        }
    }

    return valueFound;
}

struct String uncoverValid(struct String mysteryStr, struct String hiddenStr, char guess) {
	
	int x;
	
    /*
	Loop from 0 to the length of the mystery string array minus 1. 
	If the value at the current array index equals the player's guess then we must set the element at index 'x' to what the user guessed.
    */
    for (x = 0; x < strlen(mysteryStr.data); x++) {

        if (mysteryStr.data[x] == guess) {
            hiddenStr.data[x] = guess;
        }
    }

    return hiddenStr;
}

void printHangman(int currentTurn) {
	
	// The program stores each part of the hangman figure in separate variables.
	// Note that the bothLimbs variable will store both the arms and legs of the hangman figure.
    char gallows[STRMAX] =      "\n========";
    char noose[STRMAX] =        "\n|      }";
    char head[STRMAX] =         "\n|      0";
    char leftLimb[STRMAX] =     "\n|     / ";
    char body[STRMAX] =         "\n|      |";
    char bothLimbs[STRMAX] =    "\n|     / \\";
	
    /*
	The switch-case statement will evaluate the current turn the player is on, and prints a portion of the hangman figure based on the turn. 
	If the user is out of turns, then the entire figure will be printed.
    */
    switch (currentTurn) {
        case 6:
            printf("%s %s \n| \n| \n| \n|", gallows, noose);
            break;
        case 5:
            printf("%s %s %s \n| \n| \n|", gallows, noose, head);
            break;
        case 4:
            printf("%s %s %s %s \n| \n|", gallows, noose, head, leftLimb);
            break; 
        case 3:
            printf("%s %s %s %s \n| \n|", gallows, noose, head, bothLimbs);
            break;
        case 2:
            printf("%s %s %s %s %s \n|", gallows, noose, head, bothLimbs, body);
            break;
        case 1:
            printf("%s %s %s %s %s %s", gallows, noose, head, bothLimbs, body, leftLimb);
            break;
        default:
        	// If the turn is 0, then the line below will run, printing the entire figure to the screen
            printf("%s %s %s %s %s %s", gallows, noose, head, bothLimbs, body, bothLimbs);
            break;
    }
}
