// All rights reserved by Aboba Inc.


#include "InteractableItem.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"


// Sets default values
AInteractableItem::AInteractableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableItem::OnInteract(ABottomDwellerCharacter* Interactor)
{
	if (
		UInventoryComponent* InventoryComponent = Interactor->GetInventoryComponent();
		InventoryComponent &&
		InventoryComponent->AddItem(InventoryItem.DisplayName, Quantity)
	)
	{
		Destroy();
	}
}