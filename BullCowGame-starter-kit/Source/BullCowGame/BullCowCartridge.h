// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	void SetupGame();
	void ProcessingGuess(const FString Guess);
	bool IsIsogram(const FString Word) const;
	TArray<FString> GetValidWords(TArray<FString> WordList) const;
	void EndGame();

	// Your declarations go below!
	private:
	FString m_HiddenWord;
	int32	m_Lives;
	bool	m_IsGameOver;
};
