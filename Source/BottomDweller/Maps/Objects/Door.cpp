// All rights reserved by Aboba Inc.


#include "Door.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	SetRootComponent(MeshComponent);
	OpenAngle = FRotator(0, 0, 0);
	OpenOffset = FVector(0, 0, 0);
	IsTimerLocked = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}


void ADoor::AutoClose()
{
	IsTimerLocked = false;
	ChangeDoorState();
}

void ADoor::Activate_Implementation()
{
	if (IsTimerLocked)
	{
		return;
	}

	ChangeDoorState();

	if (bAutoClose)
	{
		FTimerHandle TimerHandle;
		IsTimerLocked = true;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ADoor::AutoClose, Delay, false);
	}
}

void ADoor::ChangeDoorState()
{
	switch (OpenType)
	{
	case EDoorOpenType::Rotation:
		{
			SetActorRelativeRotation(GetActorRotation() + (bIsOpened ? OpenAngle.GetInverse() : OpenAngle));
			break;
		}
	case EDoorOpenType::Slide:
		{
			SetActorLocation(GetActorLocation() + (bIsOpened ? -OpenOffset : OpenOffset));
			break;
		}
	default: ;
	}
	bIsOpened = !bIsOpened;
}

