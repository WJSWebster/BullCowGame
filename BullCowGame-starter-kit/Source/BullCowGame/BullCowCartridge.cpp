// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	SetupGame();

	PrintLine(TEXT("[The hidden word is: %s]"), *m_HiddenWord);  // debug
}

void UBullCowCartridge::SetupGame()
{
	// Welcoming player
	PrintLine(TEXT("Welcome to Bull Cows!"));

	m_HiddenWord = TEXT("cake");
	int32 wordLen = m_HiddenWord.Len();

	m_Lives = wordLen;  // the harder the word the more chances
	m_IsGameOver = false;

	PrintLine(TEXT("Guess the %i letter word! (you have that many lives)"), wordLen);
	PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));  // Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	// if game is over then ClearScreen() & SetupGame() the game
	if (m_IsGameOver)
	{
		ClearScreen();
		SetupGame();
	}
	else  // else checking PlayerGuess
	{
		ClearScreen();
		PrintLine(Input);

		ProcessingGuess(Input.ToLower());
	}
}

void UBullCowCartridge::ProcessingGuess(const FString Guess)
{
	// Checking guess
	if (Guess == m_HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
		return;
	}

	// if num of lives <= 0, end game
	if (--m_Lives <= 0)  // Remove life and check if there are any left
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *m_HiddenWord);
		EndGame();
		return;
	}

	if (Guess.Len() != m_HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %i characters long."), m_HiddenWord.Len());
	}
	else if (!IsIsogram(Guess))  // check if Isogram
	{
		PrintLine(TEXT("There are no repeating letters"));
	}
	else
	{
		int32 bulls = 0;
		int32 cows = 0;

		for (int32 i = 0; i < Guess.Len(); i++)  // iterate through each char of Input
		{
			char guessChar = Guess[i];
			if (guessChar == m_HiddenWord[i])
			{
				bulls++;
			}
			else
			{
				for (int j = 0; j < m_HiddenWord.Len(); j++)
				{
					if (guessChar == m_HiddenWord[j])
					{
						cows++;
						break;
					}
				}
			}
		}

		PrintLine(TEXT("You had %i bull%s and %i cow%s."), bulls, bulls == 1 ? TEXT("s") : TEXT(""), cows, cows == 1 ? TEXT("s") : TEXT(""));
	}


	PrintLine(TEXT("You have lost a life!\nYou now have %i %s remaining,\nguess again."), m_Lives, *FString(TEXT("live") + FString(m_Lives == 1 ? TEXT("s") : TEXT(""))));
	// else
	// guess again?
		// yes - guess again
		// no - show answer?
}

bool UBullCowCartridge::IsIsogram(const FString Word) const
{
	int32 wordLen = Word.Len();

	for (int32 i = 0; i < wordLen; i++)  // iterate through each char of Word
	{
		char currChar = Word[i];

		for (int32 j = i + 1; j < wordLen; j++)  // " "
		{
			if (currChar == Word[j])
			{
				return false;
			}
		}
	}

	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
	TArray<FString> ValidWords;

	for (int32 i = 0; i < WordList.Num(); i++)
	{
		FString word = WordList[i];
		int32 wordLen = word.Len();

		if (wordLen >= 4 && wordLen <= 8 /*&& IsIsogram(word)*/)  // this last part isn't necessary as all words in my list are isograms
		{
			ValidWords.Emplace(word);
		}
	}

	return ValidWords;
}

void UBullCowCartridge::EndGame()
{
	m_IsGameOver = true;
	PrintLine(TEXT("\nPress enter to play again."));
	// ask if player wants to play again
}