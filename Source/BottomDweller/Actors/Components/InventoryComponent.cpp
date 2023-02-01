﻿// All rights reserved by Aboba Inc.


#include "InventoryComponent.h"

#include "WeaponComponent.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/DataAssets/Items/GearItemDataAsset.h"
#include "BottomDweller/DataAssets/Items/UsableItemDataAsset.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
	switch (Item->ItemType)
	{
	case EItemType::Gear:
		{
			Equip(Item, EGearSlots::Weapon);
			ApplyGameplayEffectSpec(Spec, EGearSlots::Weapon);
			break;
		}
	case EItemType::Consumable:
		{
			if (const UUsableItemDataAsset* ConsumableItem = Cast<UUsableItemDataAsset>(Item); !ConsumableItem->bIsInfinite)
			{
				RemoveItem(Item);
			}
			ApplyGameplayEffectSpec(Spec, EGearSlots::None);
			break;
		}
	default:
		return;
	}
}

void UInventoryComponent::Equip(UItemDataAsset* Item, const EGearSlots Slot)
{
	if (!Item || !Cast<UGearItemDataAsset>(Item))
	{
		UE_LOG(LogTemp, Warning, TEXT("Only gear can be equipped"));
		return;
	}
	switch (Slot)
	{
	case EGearSlots::Weapon:
		{
			UWeaponItemDataAsset* WeaponItem = Cast<UWeaponItemDataAsset>(Item);
			ChangeWeapon(WeaponItem);
			break;
		}

	default:
		return;
	}

	RemoveItem(Item);
	OnEquipmentStateChange.Broadcast(Item, Slot);
	OnChange.Broadcast();
}

void UInventoryComponent::ChangeWeapon(UWeaponItemDataAsset* Item)
{
	const ABottomDwellerCharacter* Character = Cast<ABottomDwellerCharacter>(GetOwner());
	if (!Item || !Character || !Character->WeaponComponent)
	{
		return;
	}
	
	if (Item->SkeletalMesh.Get())
	{
		Character->WeaponComponent->SetSkeletalMesh(Item->SkeletalMesh.Get());
		Character->WeaponComponent->SetVisibility(true);
	}
	else
	{
		Character->WeaponComponent->SetVisibility(false);
	}
	
	if (EquipmentState.Weapon)
	{
		AddItem(EquipmentState.Weapon);
	}
	EquipmentState.Weapon = Item;
}

void UInventoryComponent::ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec, const EGearSlots Slot)
{
	ABottomDwellerCharacter* Character = Cast<ABottomDwellerCharacter>(GetOwner());
	UBaseAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();
	const FActiveGameplayEffectHandle Handle = ASC->ApplyGameplayEffectSpecToSelf(Spec);
	Character->RecalculateDamage();
	
	if (Spec.Duration == FGameplayEffectConstants::INSTANT_APPLICATION)
	{
		return;
	}

	if (ActiveItemHandles.Contains(Slot))
	{
		Character->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(ActiveItemHandles[Slot]);
	}
	
	ActiveItemHandles.Add(Slot, Handle);
}