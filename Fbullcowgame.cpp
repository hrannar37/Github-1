#pragma once
#include "stdafx.h"
#include "Fbullcowgame.h"
#include <map>
#define Tmap std::map

using int32 = int;

Fbullcowgame::Fbullcowgame() { Reset(); }

int32 Fbullcowgame::GetCurrentTry() const { return MyCurrentTry; }
int32 Fbullcowgame::GetHWLength() const { return MyHiddenWord.length(); }


//Resets the game at start and replay
void Fbullcowgame::Reset()
{
	FString MyHiddenWord = "";
	MyCurrentTry = 1;
	return;
}


//Sets the hidden word according to the players Decision
void Fbullcowgame::SetHiddenWord(int32 X)
{
	Tmap<int32, FString> WordLibrary{ {3, "ant"}, { 4,"lard" }, { 5,"fired" }, { 6,"stupid" }, { 7,"dormant" } };
	MyHiddenWord = WordLibrary[X];
	return;
}


//Gets the max tries based on the hidden word lenght
int32 Fbullcowgame::GetMaxTries() const
{
	Tmap<int32, int32> DifficulyCurve{ {3,6}, {4,12}, {5,18}, {6,26}, {7,35} };
	return DifficulyCurve[MyHiddenWord.length()];
}


//Checks the guess and return errors if there are any
EGuessStatus Fbullcowgame::CheckGuessValidity(FString Guess) const
{
	if (Guess == "HELP")
	{
		return EGuessStatus::HELP; //Provides help if the player asks for it
	}
	else if (!CheckIsogram(Guess)) //Guess is not an isogram
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!CheckLowercase(Guess)) //Guess contains capital letters
	{
		return EGuessStatus::CAPITAL_LETTERS;
	}
	else if (Guess.length() != GetHWLength()) //Guess is the wrong length
	{
		return EGuessStatus::WRONG_LENGHT;
	}
	else //Guess is VALID
	{
		return EGuessStatus::OK;
	}
}


//checks if the guess entered is an isogram
bool Fbullcowgame::CheckIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	Tmap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		
		if (!LetterSeen[Letter]) { LetterSeen[Letter] = true; }
		else { return false; }
	}
	return true;
}


//checks if the guess entered has any capital letters
bool Fbullcowgame::CheckLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}


//Recieves a VALID guess and Return bulls and cows
FBullCowCount Fbullcowgame::SubmitValidGuess(FString Guess)
{
	int32 HiddenWordLength = MyHiddenWord.length();

	MyCurrentTry++;
	FBullCowCount bullcowcount;

	for (int32 i = 0; i < HiddenWordLength; i++) {		//Goes through the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++) {	//goes through the guessed word
			if (Guess[j] == MyHiddenWord[i]) {			//checks every letter in the guess against the hidden word
				if (i == j) {							//sees if and where they match
					bullcowcount.Bulls++;				//increments bulls for right letter right place
				}
				else {
					bullcowcount.Cows++;				//increments cows for right letter wrong place
				}
			}
		}
	}

	return bullcowcount;
}


bool Fbullcowgame::WinOrLose(FString Guess)
{
	if (Guess == MyHiddenWord) {
		return true;
	}
	else {
		return false;
	}
}