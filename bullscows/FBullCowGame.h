#include <string>

using FString = std::string;

struct FBullCowCount {
	int Bulls = 0;
	int Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

//status after getting a user input after asking word length 
enum class EWordLengthInputStatus {
	Invalid_Status,
	Empty,
	Not_number,
	Out_of_bounds_number,
	OK
};

class FBullCowGame {
public:
	FBullCowGame();
	FBullCowGame(int WordLength);

	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	EWordLengthInputStatus CheckWordLengthValidity(FString) const;

	void Reset(int);
	FBullCowCount SubmitValidGuess(FString);

private:
	int MyCurrentTry;
	FString MyHiddenWord;
	bool GameIsWon;

	FString HiddenWordAccordingToWordLength(int) const;

	bool IsNumber(FString) const;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
