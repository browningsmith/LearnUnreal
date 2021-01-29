// Copyright Browning Keith Smith 2021


#include "OpenDoor.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
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

	ClosedAngle = GetOwner()->GetActorRotation().Yaw;
	TargetPosition = ClosedAngle;
	AnimationSpeed = DoorCloseSpeed;
	OpenAngle += ClosedAngle;

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
		TargetPosition = OpenAngle;
		AnimationSpeed = DoorOpenSpeed;
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() > DoorLastOpened + DoorOpenDelay)
	{
		TargetPosition = ClosedAngle;
		AnimationSpeed = DoorCloseSpeed;
	}

	AnimateDoor(DeltaTime);
}

void UOpenDoor::AnimateDoor(float DeltaTime)
{
	float NewYaw = FMath::Lerp(GetOwner()->GetActorRotation().Yaw, TargetPosition, DeltaTime * AnimationSpeed);
	FRotator NewRotation = {0.f, NewYaw, 0.f};
	GetOwner()->SetActorRotation(NewRotation);
}

