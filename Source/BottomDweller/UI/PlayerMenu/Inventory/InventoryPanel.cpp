// All rights reserved by Aboba Inc.


#include "InventoryPanel.h"
#include "InventorySlotWidget.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/Util/UUtils.h"
#include "Components/WrapBox.h"

bool UInventoryPanel::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(InventorySlots != nullptr)) return false;
	if (!ensure(InventoryDisplayName != nullptr)) return false;

	return bSuccess;
}

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	SetInventory(UUtils::GetInventorySubsystem(GetWorld())->GetInventoryComponent());
}

void UInventoryPanel::SetInventory(UInventoryComponent* NewInventoryComponent)
{
	InventoryComponent = NewInventoryComponent;
	InventoryComponent->OnChange.AddUniqueDynamic(this, &ThisClass::Refresh);
	Refresh();
}

void UInventoryPanel::Refresh()
{
	if (!IsValid(InventoryComponent) || !IsValid(ItemDetailsPanel)) return;

	InventorySlots->ClearChildren();
	ItemDetailsPanel->SetVisibility(ESlateVisibility::Hidden);

	for (TTuple<TSoftObjectPtr<UItemDataAsset>, int> Pair : InventoryComponent->GetInventoryContent())
	{
		UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, SlotWidget);
		InventorySlots->AddChild(InventorySlot);
		InventorySlot->InitSlot(ItemDetailsPanel, Pair.Key.Get(), Pair.Value);
	}
}
