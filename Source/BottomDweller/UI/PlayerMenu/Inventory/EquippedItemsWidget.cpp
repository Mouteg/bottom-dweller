// All rights reserved by Aboba Inc.


#include "EquippedItemsWidget.h"
#include "EquippedItemSlot.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/Util/UUtils.h"

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

	EquipmentComponent = UUtils::GetInventorySubsystem(GetWorld())->EquipmentComponent;
	EquipmentComponent->OnEquipmentStateChange.AddUniqueDynamic(this, &UEquippedItemsWidget::Update);
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
