// All rights reserved by Aboba Inc.


#include "ItemContainer.h"
#include "ItemDataAsset.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"
#include "Engine/AssetManager.h"

AItemContainer::AItemContainer()
{
	PrimaryActorTick.bCanEverTick = false;
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Container Mesh");
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	StaticMeshComponent->SetRenderCustomDepth(true);
}

void AItemContainer::OnInteract_Implementation(AActor* Interactor)
{
	if (IsValid(Interactor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Opened inter"));

		ABottomDwellerPlayerController* BottomDwellerPlayerController = Cast<ABottomDwellerPlayerController>(Interactor->GetInstigatorController());
		BottomDwellerPlayerController->OpenContainer(InventoryComponent);
	}
}

void AItemContainer::BeginPlay()
{
	InventoryComponent->AddItem(Cast<UItemDataAsset>(UAssetManager::Get().GetPrimaryAssetObject(FPrimaryAssetId("UsableItem:DA_Potion"))));
	Super::BeginPlay();
}
