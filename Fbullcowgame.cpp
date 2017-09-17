#pragma once
#include "stdafx.h"
#include "Fbullcowgame.h"
#include <stdlib.h>
#include <time.h> 
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
	srand(time(NULL));
	int32 RandomWord;
	RandomWord = rand() % 10 + 1;
	Tmap<int32, FString> WordLibrary3{ {1,"ant"}, {2,"bad"}, {3,"cat"}, {4,"sad"}, {5,"zit"}, {6,"but"}, {7,"tar"}, {8,"mit"}, {9,"bot"}, {10,"ark"} };
	Tmap<int32, FString> WordLibrary4{ {1,"slow"}, {2,"four" }, {3,"more"}, {4,"fire"}, {5,"rock"}, {6,"lake"}, {7,"dick"}, {8,"goal"}, {9,"rose"}, {10,"mole"} };
	Tmap<int32, FString> WordLibrary5{ {1,"fired" }, { 2,"slave" },{ 3,"child" },{ 4,"flake" },{ 5,"takes" },{ 6,"right" },{ 7,"spike" },{ 8,"scope" },{ 9,"brick" },{ 10,"jumpy" } };
	Tmap<int32, FString> WordLibrary6{ {1,"stupid" }, { 2,"longer" },{ 3,"sniper" },{ 4,"drying" },{ 5,"dwarfs" },{ 6,"kinder" },{ 7,"tinder" },{ 8,"boxing" },{ 9,"fumbly" },{ 10,"shrimp" } };
	Tmap<int32, FString> WordLibrary7{ {1,"dormant" }, { 2,"thwacks" },{ 3,"stumped" },{ 4,"ducking" },{ 5,"raunchy" },{ 6,"company" },{ 7,"keramic" },{ 8,"quacked" },{ 9,"zephyrs" },{ 10,"zombies" } };
	if (X == 3) { MyHiddenWord = WordLibrary3[RandomWord]; }
	else if (X == 4) { MyHiddenWord = WordLibrary4[RandomWord]; }
	else if (X == 5) { MyHiddenWord = WordLibrary5[RandomWord]; }
	else if (X == 6) { MyHiddenWord = WordLibrary6[RandomWord]; }
	else if (X == 7) { MyHiddenWord = WordLibrary7[RandomWord]; }
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