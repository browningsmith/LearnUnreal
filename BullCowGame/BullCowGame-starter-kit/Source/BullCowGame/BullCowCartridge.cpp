// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT(
        "Welcome to Bull Cows!\n"
        "Try to guess the 6 letter word.\n"
        "Press ENTER after you type your guess..."
    ));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    PrintLine(TEXT("You guessed ") + Input);
    
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("That is correct!"));
    }
    else
    {
        PrintLine(TEXT("That is incorrect, you fucking loser!"));

        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word has 6 letters."));
        }
        else
        {
            PrintLine(TEXT("You lose a life!"));
            Lives--;
        }
        
    }

    // Check if Lives is still greater than 0
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("studio");
    Lives = 6; // Same as length of HiddenWord
}