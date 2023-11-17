// All rights reserved by Aboba Inc.


#include "InventoryPanel.h"
#include "InventorySlotWidget.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
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
	
	if (IsValid(Instigator) &&  Instigator->Implements<UInventoryComponentProvider>())
	{
		SetInventory(IInventoryComponentProvider::Execute_GetInventoryComponent(GetOwningPlayerPawn()));
	}
}

void UInventoryPanel::SetInventory(UInventoryComponent* NewInventoryComponent)
{
	if (IsValid(Instigator) &&  Instigator->Implements<UInventoryComponentProvider>())
	{
		InventoryComponent = NewInventoryComponent;
		InventoryComponent->OnChange.AddUniqueDynamic(this, &ThisClass::Refresh);
	}
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
		InventorySlot->Instigator = Instigator;
		InventorySlot->SetItem(Pair.Key.Get(), Pair.Value);
		InventorySlot->ItemDetailsPanel = ItemDetailsPanel;
	}
}
