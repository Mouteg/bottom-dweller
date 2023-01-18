// All rights reserved by Aboba Inc.


#include "PressurePlate.h"

#include "BottomDweller/Maps/Activatable.h"
#include "Engine/TriggerBox.h"

UPressurePlate::UPressurePlate()
{
	TriggerBox = CreateDefaultSubobject<ATriggerBox>(TEXT("TriggerBox"));
	TriggerBox->OnActorBeginOverlap.AddDynamic(this, &UPressurePlate::OnOverlap);
}

void UPressurePlate::OnOverlap(AActor* ActorOverlapped, AActor* OtherActor)
{
	if (OtherActor->Implements<UActivatable>())
	{
		IActivatable::Execute_Activate(OtherActor);
	}
}
