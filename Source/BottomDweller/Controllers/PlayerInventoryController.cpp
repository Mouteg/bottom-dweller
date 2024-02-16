// All rights reserved by Aboba Inc.


#include "PlayerInventoryController.h"

#include "BottomDwellerPlayerController.h"
#include "BottomDweller/UI/PlayerMenu/Inventory/InventoryPanel.h"
#include "BottomDweller/Util/UUtils.h"

void UPlayerInventoryController::Deinitialize()
{
	Super::Deinitialize();
}

void UPlayerInventoryController::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPlayerInventoryController::Equip(UItemDataAsset* Item)
{
	EquipmentComponent->Equip(Item);
}

int32 UPlayerInventoryController::AddItem(UItemDataAsset* Item, const int32 Quantity)
{
	return InventoryComponent->AddItem(Item, Quantity);
}

void UPlayerInventoryController::RemoveItem(const UItemDataAsset* Item, const int32 Quantity)
{
	InventoryComponent->RemoveItem(Item, Quantity);
}

void UPlayerInventoryController::UseItem(UItemDataAsset* Item, FGameplayEffectSpec& Spec)
{
	InventoryComponent->UseItem(Item, Spec);
}


void UPlayerInventoryController::OpenContainer(const TObjectPtr<UInventoryComponent> ContainerInventoryComponent, const FString& ContainerName)
{
	if (IsValid(ContainerInventoryPanel))
	{
		ABottomDwellerPlayerController* BottomDwellerPlayerController = UUtils::GetPlayerController(GetWorld());
		BottomDwellerPlayerController->SetGameMenuVisible();
		ContainerInventoryPanel->SetVisibility(ESlateVisibility::Visible);
		ContainerInventoryPanel->SetInventory(ContainerInventoryComponent, ContainerName);
	}

	// Open container menu
	// Set slots
	// Set container widget visible
}
