// All rights reserved by Aboba Inc.


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
}

void AInteractableItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (InventoryItem)
	{
		StaticMesh->SetStaticMesh(InventoryItem->Mesh.Get());
		StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	}
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
		InventoryComponent
	)
		Quantity = InventoryComponent->AddItem(InventoryItem, Quantity);
	if (Quantity <= 0)
	{
		Destroy();
	}
}
