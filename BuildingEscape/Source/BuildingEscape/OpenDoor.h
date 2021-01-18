// Copyright Browning Keith Smith 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AnimateDoor(float DeltaTime);

private:
	float ClosedAngle;
	float TargetPosition;
	float AnimationSpeed;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenDelay = 3.f;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 3.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 3.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	AActor* ActorThatOpensDoor;
};
