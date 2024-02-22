// All rights reserved by Aboba Inc.


#include "EquipmentComponent.h"
#include "WeaponComponent.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/DataAssets/Items/GearItemDataAsset.h"
#include "BottomDweller/Util/UUtils.h"


UEquipmentComponent::UEquipmentComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UEquipmentComponent::BeginPlay() {
	Super::BeginPlay();
}


void UEquipmentComponent::Equip(UGearItemDataAsset* Item) {
	if (!IsValid(Item)) {
		UE_LOG(LogTemp, Warning, TEXT("Not valid item equipped"));
		return;
	}
	ChangeEquipment(Item);

	UUtils::GetInventorySubsystem(GetWorld())->RemoveItem(Item);
	OnEquipmentStateChange.Broadcast(Item, Item->ItemType);
}

void UEquipmentComponent::Unequip(const EItemType ItemType) {
	if (EquipmentState.Contains(ItemType)) {
		UUtils::GetInventorySubsystem(GetWorld())->AddItem(EquipmentState[ItemType]);
	}
	EquipmentState.Remove(ItemType);
	SwitchWeaponMesh(nullptr, Cast<ABottomDwellerCharacter>(GetOwner()));
	OnEquipmentStateChange.Broadcast(nullptr, ItemType);
}

void UEquipmentComponent::SwitchWeaponMesh(UGearItemDataAsset* Item, const ABottomDwellerCharacter* Character) {
	if (Item && Item->SkeletalMesh.Get()) {
		Character->WeaponComponent->SetSkeletalMesh(Item->SkeletalMesh.Get());
		Character->WeaponComponent->SetVisibility(true);
	} else {
		Character->WeaponComponent->SetVisibility(false);
	}
}

void UEquipmentComponent::ChangeEquipment(UGearItemDataAsset* Item) {
	const ABottomDwellerCharacter* Character = Cast<ABottomDwellerCharacter>(GetOwner());
	if (!Item || !Character || !Character->WeaponComponent) {
		return;
	}

	switch (Item->ItemType) {
	case EItemType::Weapon:
		SwitchWeaponMesh(Item, Character);
		break;
	case EItemType::Armor:
		break;
	case EItemType::Consumable:
		break;
	}

	if (EquipmentState.Contains(Item->ItemType)) {
		UUtils::GetInventorySubsystem(GetWorld())->AddItem(EquipmentState[Item->ItemType]);
	}
	EquipmentState.Add(Item->ItemType, Item);
}
