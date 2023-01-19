// All rights reserved by Aboba Inc.


#include "PressurePlate.h"

#include "BottomDweller/Maps/Activatable.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"

APressurePlate::APressurePlate()
{
	bOneTimeUse = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Plate collision"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate Mesh"));
	SetRootComponent(BoxComponent);
	MeshComponent->SetupAttachment(BoxComponent);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlap);
}

void APressurePlate::OnOverlap(AActor* ActorOverlapped, AActor* OtherActor)
{

	for (AActor* Actor : ObjectsToActivate)
	{
		if (Actor->Implements<UActivatable>())
		{
			//play sound, maybe animation
			IActivatable::Execute_Activate(Actor);
		}
	}
	if (bOneTimeUse)
	{
		Destroy();
	}
}
