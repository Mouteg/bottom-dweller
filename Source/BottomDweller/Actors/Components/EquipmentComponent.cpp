// All rights reserved by Aboba Inc.


#include "EquipmentComponent.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/DataAssets/Items/GearItemDataAsset.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"
#include "BottomDweller/UI/PlayerMenu/Inventory/EquippedItemSlot.h"


UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	InventoryComponent = IComponentProviderSupport::Execute_GetInventoryComponent(GetOwner());
}


void UEquipmentComponent::Equip(UItemDataAsset* Item)
{
	if (!IsValid(Item) || !Cast<UGearItemDataAsset>(Item))
	{
		UE_LOG(LogTemp, Warning, TEXT("Only gear can be equipped"));
		return;
	}

	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		{
			UWeaponItemDataAsset* WeaponItem = Cast<UWeaponItemDataAsset>(Item);
			ChangeWeapon(WeaponItem);
			break;
		}

	default:
		UE_LOG(LogTemp, Warning, TEXT("Unrecognized item type"));
		return;
	}

	InventoryComponent->RemoveItem(Item);
	OnEquipmentStateChange.Broadcast(Item, Item->ItemType);
}

void UEquipmentComponent::ChangeWeapon(UWeaponItemDataAsset* Item)
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
		InventoryComponent->AddItem(EquipmentState.Weapon);
	}
	EquipmentState.Weapon = Item;
}

