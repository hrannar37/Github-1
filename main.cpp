#pragma once
#include "stdafx.h"
#include "Fbullcowgame.h"

using FText = std::string;
using int32 = int;

void Intro();
void SetDifficulty();
void PlayGame();
void EndGameMSG(FText);
FText FAQ();
bool ReplayGame();


Fbullcowgame BCGame;


int main()
{
	do
	{
		Intro();
		PlayGame();
	} 
	while (ReplayGame());
	return 0;

}


void Intro()
{
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "Type in ""HELP"" for some useful info\n\n";
	SetDifficulty();
	std::cout << "You have " << BCGame.GetMaxTries() << " Tries\n";
	std::cout << "Good Luck";
	std::cout << std::endl;
	return;
}


void SetDifficulty()
{
	FText I = "";
	double C;
	int32 O;
	
	std::cout << "Choose the Hidden Word LENGTH (3-7): ";

	while (true)
	{
		while (std::getline(std::cin, I))
		{
			std::stringstream ss(I);
			if (I == "HELP") {
				std::cout << "\nThis option sets the lenght of the word you need to guess\n";
				std::cout << "The Lenght of the Hidden Word defines the difficulty of the game\n\n";
			}
			else if (ss >> C)
			{
				if (ss.eof()) {	break; }
			}
			std::cout << "Please enter a valid number\n";
		}
		if ((3 <= C) && (C <= 7))
		{
			O = (C);
			BCGame.SetHiddenWord(O);
			return;
		}
		else { std::cout << "Please enter a valid number between 3 and 7\n"; }
	}
	return;
}


void PlayGame()
{
	BCGame.Reset();
	FText Guess = "";
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.WinOrLose(Guess) && BCGame.GetCurrentTry() <=MaxTries)
	{
		Guess = FAQ();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	EndGameMSG(Guess);
	return;
}


FText FAQ()
{
	EGuessStatus Status = EGuessStatus::INVALID;
	FText GuessInput;
	
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " Enter your guess:";
		std::getline(std::cin, GuessInput);

		Status = BCGame.CheckGuessValidity(GuessInput);
		switch (Status) {

		case EGuessStatus::HELP:
			std::cout << "\nwhen you enter a valid guess you get back BULLS and COWS\n";
			std::cout << "COWS stand for correct letters in wrong places\n";
			std::cout << "And BULLS stand for correct letters in correct places\n";
			break;

		case EGuessStatus::WRONG_LENGHT:
			std::cout << "Please enter a " << BCGame.GetHWLength() << " letter word! \n";
			break;

		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a word without repeating letters!\n";
			break;

		case EGuessStatus::CAPITAL_LETTERS:
			std::cout << "Your guess must only contain NORMAL and LOWERCASE letters\n";
			break;

		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //Keep looping until we get no errors
	return GuessInput;
}


void EndGameMSG(FText Guess)
{
	if (BCGame.WinOrLose(Guess)) {
		std::cout << "You guessed the right word. Well Done\n\n";
		return;
	}
	else {
		std::cout << "Better Luck Next Time!\n\n";
		return;
	}
}


bool ReplayGame()
{
	FText Response = "";

	std::cout << "Do you want to play again (Y/N)";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'Y') || (Response[0] == 'y');
}
