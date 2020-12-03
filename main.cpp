// Rules
// 1. The player will match the values randomly generated by the computer.
// (컴퓨터가 랜덤하게 생성한 값을 플레이어가 맞춘다.)
// 2. The player can expect the generated string and enter it once per turn.
// (플레이어는 생성된 문자열을 예상하여 1턴에 1번씩 입력할 수 있다.)
// 3. Compare the string you entered to the correct answer and
// 플레이어가 입력한 문자열을 정답과 비교하여 값과 위치가 모두 맞는 문자의 갯수를 'Bulls'
// 위치는 틀렸지만 값은 맞는 문자의 갯수를 'Cows'로 카운트

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();
int32 GetValidUserWordLength();

FBullCowGame BCGame;

//if game is finished successfully, ask player to play again
int main() {

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro() {

	std::cout << "Welcome to Bulls and CAUs.\n";
	std::cout << "*CAUTION : COWS? (X) CAUs? (O) ꉂꉂ(ᵔᗜᵔ*)\n";
	std::cout << std::endl;
	std::cout << "          }   {         †    人    † " << std::endl;
	std::cout << "          (o o)         † ◞     ◟ † " << std::endl;
	std::cout << "   /-------\\ /         ʕ⸝          ⸜ʔ" << std::endl;
	std::cout << "  / | BULL |O        ~~(~๑ ●ิ .. ● ิ๑ ~) ~~    " << std::endl;
	std::cout << " *  |-,--- |            ◟    ‿    ◞      "<< std::endl;
	std::cout << "    ^      ^             *･･･････････*   " << std::endl;
	std::cout << "                            CAU      " << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " unique letters I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//plays a game
void PlayGame() {

	int32 WordLength = GetValidUserWordLength();
	BCGame.Reset(WordLength);

	int32 MaxTries = BCGame.GetMaxTries();

	//while loop for the guess(while the game is not won & tries left)
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		//submit valid guess to the game & receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";

	}

	PrintGameSummary();
	return;
}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again? press the button! --> (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

//loop continually until the user gives valid input
FText GetValidGuess() {

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << std::endl;

		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with unique letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get a valid input

	return Guess;
}

void  PrintGameSummary() {

	if (BCGame.IsGameWon()) {
		std::cout << "Well done! You did it!\n";
	}
	else {
		std::cout << "Don't mind... You can do better next time!\n";
	}

	return;
}

//loops until it gets valid word length from user
int32 GetValidUserWordLength() {

	EWordLengthInputStatus WordLengthStatus = EWordLengthInputStatus::Invalid_Status;
	FString Input = "";
	int32 Length = 0;

	do {
		std::cout << "Please, enter your desirable word length.\n";
		std::getline(std::cin, Input);

		WordLengthStatus = BCGame.CheckWordLengthValidity(Input);
		switch (WordLengthStatus) {
		case EWordLengthInputStatus::Empty:
			std::cout << "Don't enter an empty string.\n\n";
			break;
		case EWordLengthInputStatus::Not_number:
			std::cout << "Please enter a number, not words.\n\n";
			break;
		case EWordLengthInputStatus::Out_of_bounds_number:
			std::cout << "Please enter a number between 3 and 7, these included.\n\n";
			break;
		default:
			//assume the guess is valid
			Length = std::stoi(Input);
			break;
		}
	} while (WordLengthStatus != EWordLengthInputStatus::OK); //keep the loop until we get a valid input

	return Length;
}
