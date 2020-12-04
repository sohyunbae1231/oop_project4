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

	int GetMaxTries() const;    // 최대 시도 가능 횟수
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const; 
	EGuessStatus CheckGuessValidity(FString) const; 
	EWordLengthInputStatus CheckWordLengthValidity(FString) const;

	void Reset(int);
	FBullCowCount SubmitValidGuess(FString);

private:
	int MyCurrentTry;   // 시도횟수
	FString MyHiddenWord;   // 지정한 단어
	bool GameIsWon; // 게임 이겼는지 여부

	FString HiddenWordAccordingToWordLength(int) const;

	bool IsIsogram(FString) const;  // unique letter로 되어있는지 여부
	bool IsLowerCase(FString) const;    // 영어 소문자(대문자x, 숫자x)로 되어있는지 여부 
	// -> 사용자가 입력한 문자가 영어 소문자이면 받아들이고 아니면 다시 입력
};
