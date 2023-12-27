// All rights reserved by Aboba Inc.


#include "InventoryUI.h"

#include "EquippedItemsWidget.h"
#include "InventoryPanel.h"

bool UInventoryUI::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(EquippedItemsWidget != nullptr)) return false;
	if (!ensure(InventoryPanel != nullptr)) return false;
	if (!ensure(ItemDetailsPanel != nullptr)) return false;
	if (!ensure(ContainerInventoryPanel != nullptr)) return false;
	
	if (EquippedItemsWidget && InventoryPanel && ItemDetailsPanel && ContainerInventoryPanel)
	{
		InventoryPanel->ItemDetailsPanel = ItemDetailsPanel;
		ContainerInventoryPanel->ItemDetailsPanel = ItemDetailsPanel;
		EquippedItemsWidget->ItemDetailsPanel = ItemDetailsPanel;
	}
	
	return bSuccess;
}

void UInventoryUI::NativePreConstruct()
{
	Super::NativeConstruct();
}