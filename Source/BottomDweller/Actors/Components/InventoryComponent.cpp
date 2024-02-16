// All rights reserved by Aboba Inc.


#include "InventoryComponent.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/DataAssets/Items/GearItemDataAsset.h"
#include "BottomDweller/DataAssets/Items/UsableItemDataAsset.h"
#include "BottomDweller/Util/UUtils.h"

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
		return 0;
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
		{
			InventoryContent.Add(Item, 1);
		}
	}

	OnChange.Broadcast();
	return Quantity -AmountToReturn;
}

void UInventoryComponent::AddItems(UInventoryComponent* Inventory)
{
	for (auto ItemQuantityPair : Inventory->GetInventoryContent())
	{
		const int32 ItemsAdded = AddItem(ItemQuantityPair.Key.Get(), ItemQuantityPair.Value);
		Inventory->RemoveItem(ItemQuantityPair.Key.Get(), ItemsAdded);
	}
}

void UInventoryComponent::RemoveItem(const UItemDataAsset* Item, const int32 Quantity)
{
	if (!InventoryContent.Contains(Item))
	{
		return;
	}

	if (InventoryContent[Item] > Quantity)
	{
		InventoryContent[Item] -= Quantity;
	}
	else
	{
		InventoryContent.Remove(Item);
	}
	OnChange.Broadcast();
}

void UInventoryComponent::UseItem(UItemDataAsset* Item, FGameplayEffectSpec& Spec)
{
	if (Item->IsA(UGearItemDataAsset::StaticClass()))
	{
		UUtils::GetInventorySubsystem(GetWorld())->Equip(Item);
	}
	else if (const UUsableItemDataAsset* ConsumableItem = Cast<UUsableItemDataAsset>(Item); ConsumableItem && !ConsumableItem->bIsInfinite)
	{
		RemoveItem(Item);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unrecognized item type"));
		return;
	}

	ApplyGameplayEffectSpec(Spec, Item->ItemType);
	OnChange.Broadcast();
}

void UInventoryComponent::ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec, const EItemType Slot)
{
	if (!GetOwner()->Implements<UASCProviderSupport>())
	{
		return;
	}
	UBaseAbilitySystemComponent* ASC = IASCProviderSupport::Execute_GetASCComponent(GetOwner());
	const FActiveGameplayEffectHandle Handle = IASCProviderSupport::Execute_GetASCComponent(GetOwner())->ApplyGameplayEffectSpecToSelf(Spec);

	ABottomDwellerCharacter* Character = Cast<ABottomDwellerCharacter>(GetOwner());

	if (ActiveItemHandles.Contains(Slot) && Spec.Duration == FGameplayEffectConstants::INFINITE_DURATION)
	{
		ASC->RemoveActiveGameplayEffect(ActiveItemHandles[Slot]);
	}
	ActiveItemHandles.Add(Slot, Handle);
	Character->RecalculateDamage();
}
