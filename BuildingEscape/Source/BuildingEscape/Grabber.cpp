// Copyright Browning Keith Smith 2021

#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT(
			"Actor %s does not have a PhysicsHandleComponent.\n"
			"Make sure a PhysicsHandle component is added to %s."
		), *GetOwner()->GetName(), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(
			LogTemp, Error, TEXT("Actor %s could not find InputComponent. Make sure Input is enabled."),
			*GetOwner()->GetName()
		);
	}
	else
	{
		UE_LOG(
			LogTemp, Warning, TEXT("Actor %s found InputComponent."),
			*GetOwner()->GetName()
		);
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewPosition;
	FRotator ViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewPosition, OUT ViewRotation);

	// Draw Debug Line
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

	// Ray Cast out to test for objects to grab
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewPosition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("We hit %s!"), *(Hit.Actor->GetName()));
	}
	// else
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("We missed!"));
	// }
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing key pressed!"));
}

