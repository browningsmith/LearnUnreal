// Fill out your copyright notice in the Description page of Project Settings.
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    LoadWordList();
    GetValidWords();

    SetupGame();
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

void UBullCowCartridge::LoadWordList()
{
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
}

void UBullCowCartridge::GetValidWords()
{
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8)
        {
            if (IsIsogram(Word))
            {
                ValidWordList.Emplace(Word);
            }
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = &ValidWordList[FMath::RandHelper(ValidWordList.Num())]; // Select a random word from ValidWordList
    // PrintLine(TEXT("The hidden word is %s"), **HiddenWord);
    Lives = (*HiddenWord).Len();
    bGameIsOver = false;

    PrintLine(
        TEXT(
            "Welcome to Bull Cows!\n"
            "Try to guess the %i letter word.\n"
            "You have %i lives left.\n"
            "Press ENTER after you type your guess..."
        ),
        (*HiddenWord).Len(),
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
    
    if (Guess == *HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("That is correct! You Win!"));
        EndGame();
        return;
    }

    PrintLine(TEXT("That is incorrect, you fucking loser!"));

    if (Guess.Len() != (*HiddenWord).Len())
    {
        PrintLine(TEXT("The Hidden Word has %i letters."), (*HiddenWord).Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The Hidden Word has no repeating letters."));
        return;
    }

    PrintLine(TEXT("You lost a life like an idiot!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(
            TEXT("Aaaand you lost. What a fucking surprise.\nThe hidden word was %s."),
            **HiddenWord
        );
        EndGame();
        return;
    }

    FBullCowCount Count;
    GetBullCows(Guess, Count);
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Count.Bulls, Count.Cows);

    PrintLine(TEXT("You have %i lives left."), Lives);
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

void UBullCowCartridge::GetBullCows(const FString& Guess, FBullCowCount& OutBullCowCount) const
{
    OutBullCowCount.Bulls = 0;
    OutBullCowCount.Cows = 0;

    for (int32 I = 0; I < Guess.Len(); I++)
    {
        if (Guess[I] == (*HiddenWord)[I])
        {
            ++OutBullCowCount.Bulls;
            continue;
        }

        for (int32 J = 0; J < Guess.Len(); J++)
        {
            if (Guess[I] == (*HiddenWord)[J])
            {
                ++OutBullCowCount.Cows;
                break;
            }
        }
    }
}