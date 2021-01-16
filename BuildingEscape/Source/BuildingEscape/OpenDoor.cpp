// Copyright Browning Keith Smith 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += StartingYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s has OpenDoor component, but PressurePlate is null"), *(GetOwner()->GetName()));
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		CloseDoor(DeltaTime);
	}
	else
	{
		OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	float NewYaw = FMath::Lerp(GetOwner()->GetActorRotation().Yaw, TargetYaw, DeltaTime * 3.f);
	FRotator NewRotation = {0.f, NewYaw, 0.f};
	GetOwner()->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float NewYaw = FMath::Lerp(GetOwner()->GetActorRotation().Yaw, StartingYaw, DeltaTime * 3.f);
	FRotator NewRotation = {0.f, NewYaw, 0.f};
	GetOwner()->SetActorRotation(NewRotation);
}

