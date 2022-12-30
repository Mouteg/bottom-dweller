// All rights reserved by Aboba Inc.


#include "InventoryComponent.h"

#include "BottomDweller/DataAssets/Items/GearItemDataAsset.h"
#include "BottomDweller/DataAssets/Items/UsableItemDataAsset.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

int32 UInventoryComponent::AddItem(UItemDataAsset* Item, const int32 Quantity)
{
	if (Quantity <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Quantity <= 0"))
	}

	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Item"));
		return 0;
	}

	int32 AmountToReturn;
	const bool IsContained = InventoryContent.Contains(Item);

	if (Item->bIsStackable)
	{
		const int32 SumQuantity = (IsContained ? InventoryContent[Item] : 0) + Quantity;
		AmountToReturn = FMath::Max(SumQuantity - Item->MaxStack, 0);
		if (IsContained)
		{
			InventoryContent[Item] = FMath::Min(SumQuantity, Item->MaxStack);
		}
		else
		{
			InventoryContent.Add(Item, FMath::Min(Quantity, Item->MaxStack));
		}
	}
	else
	{
		AmountToReturn = IsContained ? Quantity : Quantity - 1;
		if (!IsContained)
			InventoryContent.Add(Item, 1);
	}

	OnChange.Broadcast();
	return AmountToReturn;
}

void UInventoryComponent::RemoveItem(const UItemDataAsset* Item, const int32 Quantity)
{
	if (InventoryContent.Contains(Item) && InventoryContent[Item] > Quantity)
	{
		InventoryContent[Item] -= Quantity;
	}
	else
	{
		InventoryContent.Remove(Item);
	}
	OnChange.Broadcast();

	UE_LOG(LogTemp, Warning, TEXT("Item removed %s"), *Item->DisplayName.ToString())
}

void UInventoryComponent::UseItem(UItemDataAsset* Item)
{
	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		{
			Equip(Item, Weapon);
			break;
		}
	case EItemType::Consumable:
		{
			UUsableItemDataAsset* ConsumableItem = Cast<UUsableItemDataAsset>(Item);
			RemoveItem(Item, 48);
			break;
		}
	default:
		;
	}
}

void UInventoryComponent::Equip(UItemDataAsset* Item, const EEquipmentItems Slot)
{
	if (!Item || !Item->Implements<UGearItemDataAsset>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Only gear can be equipped"));
		return;
	}

	switch (Slot)
	{
	case Weapon:
		{
			UWeaponItemDataAsset* WeaponItem = Cast<UWeaponItemDataAsset>(Item);
			if (!WeaponItem)
			{
				return;
			}

			EquipmentState.Weapon = WeaponItem;
			break;
		}

	default:
		return;
	}

	RemoveItem(Item, 1);
	OnEquipmentStateChange.Broadcast();
	OnChange.Broadcast();
}
