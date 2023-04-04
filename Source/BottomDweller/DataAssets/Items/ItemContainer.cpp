// All rights reserved by Aboba Inc.


#include "ItemContainer.h"

AItemContainer::AItemContainer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItemContainer::OnInteract_Implementation(AActor* Interactor)
{
	// Open container menu
}

void AItemContainer::BeginPlay()
{
	Super::BeginPlay();
}

