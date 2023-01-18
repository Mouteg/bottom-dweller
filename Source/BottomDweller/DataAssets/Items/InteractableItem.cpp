﻿// All rights reserved by Aboba Inc.


#include "InteractableItem.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"


// Sets default values
AInteractableItem::AInteractableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Item mesh");
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void AInteractableItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (InventoryItem && StaticMesh)
	{
		StaticMesh->SetStaticMesh(InventoryItem->Mesh.Get());
	}
}

void AInteractableItem::OnInteract_Implementation(AActor* Interactor)
{
	const ABottomDwellerCharacter* Character = Cast<ABottomDwellerCharacter>(Interactor);
	UInventoryComponent* InventoryComponent = Character->GetInventoryComponent();
	if (Character && InventoryComponent)
	{
		Quantity = InventoryComponent->AddItem(InventoryItem, Quantity);
	}
	if (Quantity <= 0)
	{
		Destroy();
	}
}