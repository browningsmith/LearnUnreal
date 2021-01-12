// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Initialize hidden word
    HiddenWord = TEXT("studio");

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
        PrintLine("That is correct!");
    }
    else
    {
        PrintLine("That is incorrect, you fking loser!");
    }
}