﻿// All rights reserved by Aboba Inc.


#include "EquippedItemsWidget.h"
#include "EquippedItemSlot.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

bool UEquippedItemsWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(WeaponSlot != nullptr)) return false;

	return bSuccess;
}

void UEquippedItemsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (GetOwningPlayerPawn()->Implements<UComponentProviderSupport>())
	{
		InventoryComponent = IComponentProviderSupport::Execute_GetInventoryComponent(GetOwningPlayerPawn());
		InventoryComponent->OnEquipmentStateChange.AddUniqueDynamic(this, &UEquippedItemsWidget::Update);
	}
	InitSlots();
}

void UEquippedItemsWidget::InitSlots()
{
	WeaponSlot->EquipmentSlot = EItemType::Weapon;
	EquipSlots.Add(WeaponSlot->EquipmentSlot, WeaponSlot);
}

void UEquippedItemsWidget::Update(UItemDataAsset* Item, EItemType GearSlot)
{
	//Move so it only happens once, cant use construct. Create player menu widget
	if (ItemDetailsPanel)
	{
		EquipSlots[GearSlot]->ItemDetailsPanel = ItemDetailsPanel;
	}
	EquipSlots[GearSlot]->SetItem(Item);
}
