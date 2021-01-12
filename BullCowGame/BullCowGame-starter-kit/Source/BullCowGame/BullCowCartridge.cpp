// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    // PrintLine(TEXT("The Hidden Word is %s.\nIt is %i characters long."), *HiddenWord, HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    if (bGameIsOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        PrintLine(TEXT("You guessed ") + Input);
    
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("That is correct! You Win!"));
            EndGame();
        }
        else
        {
            PrintLine(TEXT("That is incorrect, you fucking loser!"));

            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word has %i letters."), HiddenWord.Len());
            }
            else
            {
                PrintLine(TEXT("You lost a life like an idiot!"));
                --Lives;
            }

            if (Lives <= 0)
            {
                PrintLine(TEXT("Aaaand you lost. What a fucking surprise."));
                EndGame();
            }
            else
            {
                PrintLine(TEXT("You have %i lives left."), Lives);
            }
        }
    }  
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("studio");
    Lives = HiddenWord.Len();
    bGameIsOver = false;

    PrintLine(
        TEXT(
            "Welcome to Bull Cows!\n"
            "Try to guess the %i letter word.\n"
            "You have %i lives left.\n"
            "Press ENTER after you type your guess..."
        ),
        HiddenWord.Len(),
        Lives
    );
}

void UBullCowCartridge::EndGame()
{
    bGameIsOver = true;
    PrintLine(TEXT("GAME OVER\nPress ENTER to play again you\nfucking no life bitch."));
}