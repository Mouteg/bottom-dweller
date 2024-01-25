// All rights reserved by Aboba Inc.


#include "PlayerInventoryController.h"

#include "BottomDweller/UI/PlayerMenu/Inventory/InventoryPanel.h"

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


void UPlayerInventoryController::OpenContainer(const TObjectPtr<UInventoryComponent> ContainerInventoryComponent, FString ContainerName)
{
	if (IsValid(ContainerInventoryPanel))
	{
		ContainerInventoryPanel->SetInventory(ContainerInventoryComponent, ContainerName);
	}

	// Open container menu
	// Set slots
	// Set container widget visible
}
