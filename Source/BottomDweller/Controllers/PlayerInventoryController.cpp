// All rights reserved by Aboba Inc.


#include "PlayerInventoryController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BottomDwellerPlayerController.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "BottomDweller/UI/PlayerMenu/Inventory/InventoryPanel.h"
#include "BottomDweller/Util/UUtils.h"

void UPlayerInventoryController::Deinitialize()
{
	Super::Deinitialize();
}

void UPlayerInventoryController::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UseItemEventTag = Tag_Event_UseItem;
}

void UPlayerInventoryController::Equip(UItemDataAsset* Item)
{
	EquipmentComponent->Equip(Item);
}

int32 UPlayerInventoryController::AddItem(UItemDataAsset* Item, const int32 Quantity)
{
	return InventoryComponent->AddItem(Item, Quantity);
}

void UPlayerInventoryController::AddItems(UInventoryComponent* Inventory)
{
	return InventoryComponent->AddItems(Inventory);
}

void UPlayerInventoryController::RemoveItem(const UItemDataAsset* Item, const int32 Quantity)
{
	InventoryComponent->RemoveItem(Item, Quantity);
}

void UPlayerInventoryController::UseItem(UItemDataAsset* Item)
{
	FGameplayEventData EventData;
	EventData.OptionalObject = Item;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(UUtils::GetPlayerController(GetWorld())->GetCharacter(), UseItemEventTag, EventData);
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
