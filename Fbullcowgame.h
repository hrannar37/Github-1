#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	INVALID,
	HELP,
	OK,
	NOT_ISOGRAM,
	CAPITAL_LETTERS,
	BAD_CHARACTERS,
	WRONG_LENGHT,
	GUESS_REPEAT,
};

class Fbullcowgame
{
public:
	
	Fbullcowgame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHWLength() const;

	EGuessStatus CheckGuessValidity(FString Guess) const;
	void SetHiddenWord(int32);

	FBullCowCount SubmitValidGuess(FString);
	bool WinOrLose(FString);
	void Reset();
	
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;

	bool CheckIsogram(FString) const;
	bool CheckLowercase(FString) const;
};