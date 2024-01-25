// All rights reserved by Aboba Inc.


#include "ItemContainer.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "BottomDweller/Util/UUtils.h"
#include "Engine/AssetManager.h"

AItemContainer::AItemContainer()
{
	PrimaryActorTick.bCanEverTick = false;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Container Mesh");
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	StaticMeshComponent->SetRenderCustomDepth(true);
	ContainerName = "Chest";
}

void AItemContainer::OnInteract_Implementation(AActor* Interactor)
{
	if (IsValid(Interactor))
	{
		UUtils::GetInventorySubsystem(GetWorld())->OpenContainer(InventoryComponent, ContainerName);
	}
}

void AItemContainer::BeginPlay()
{
	//For testing purposes
	InventoryComponent->AddItem(Cast<UItemDataAsset>(UAssetManager::Get().GetPrimaryAssetObject(FPrimaryAssetId("UsableItem:DA_Potion"))));
	Super::BeginPlay();
}
