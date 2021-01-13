// Fill out your copyright notice in the Description page of Project Settings.
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);

    SetupGame();

    PrintLine(TEXT("There are %i words in HiddenWordList"), WordList.Num());
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
        ProcessGuess(Input);
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

    const TCHAR HiddenWordArray[] = TEXT("studio");
}

void UBullCowCartridge::EndGame()
{
    bGameIsOver = true;
    PrintLine(TEXT("GAME OVER\nPress ENTER to play again you\nfucking no life bitch."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    PrintLine(TEXT("You guessed ") + Guess);
    
    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("That is correct! You Win!"));
        EndGame();
        return;
    }

    PrintLine(TEXT("That is incorrect, you fucking loser!"));

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word has %i letters."), HiddenWord.Len());
    }
    else if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The Hidden Word has no repeating letters."));
    }
    else
    {
        PrintLine(TEXT("You lost a life like an idiot!"));
        --Lives;
    }

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(
            TEXT("Aaaand you lost. What a fucking surprise.\nThe hidden word was %s."),
            *HiddenWord
        );
        EndGame();
    }
    else
    {
        PrintLine(TEXT("You have %i lives left."), Lives);
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 I = 0; I < Word.Len(); I++)
    {
        for (int32 J = I + 1; J < Word.Len(); J++)
        {
            if (I == J)
            {
                continue;
            }

            if (Word[I] == Word[J])
            {
                return false;
            }
        }
    }

    return true;
}