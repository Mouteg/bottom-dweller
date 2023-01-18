// All rights reserved by Aboba Inc.


#include "InventoryUI.h"

#include "EquippedItemsWidget.h"
#include "InventoryPanel.h"

bool UInventoryUI::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	return bSuccess;
}

void UInventoryUI::NativePreConstruct()
{
	Super::NativeConstruct();
	if (EquippedItemsWidget && InventoryPanel && ItemDetailsPanel)
	{
		InventoryPanel->ItemDetailsPanel = ItemDetailsPanel;
		EquippedItemsWidget->ItemDetailsPanel = ItemDetailsPanel;
	}
}