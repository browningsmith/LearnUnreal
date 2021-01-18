// Copyright Browning Keith Smith 2021

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is ready to grab ;)"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewPosition;
	FRotator ViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPosition, OUT ViewRotation);

	FVector LineTraceEnd = ViewPosition + ViewRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		ViewPosition,
		LineTraceEnd,
		FColor(255, 0, 0, 255),
		false,
		(-1.0F),
		(uint8)'\000',
		(3.0F)
	);
}

