// All rights reserved by Aboba Inc.


#include "InventoryPanel.h"
#include "InventorySlotWidget.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/Util/UUtils.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

bool UInventoryPanel::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	if (!ensure(InventorySlots != nullptr)) return false;
	if (!ensure(InventoryDisplayName != nullptr)) return false;
	if (!ensure(TakeAllButton != nullptr)) return false;

	TakeAllButton->OnClicked.AddDynamic(this, &ThisClass::UInventoryPanel::TakeAll);

	return bSuccess;
}

void UInventoryPanel::NativeConstruct()
{
	Super::NativeConstruct();

	SetInventory(UUtils::GetInventorySubsystem(GetWorld())->GetInventoryComponent());
}

void UInventoryPanel::SetInventory(UInventoryComponent* NewInventoryComponent, const FString& ContainerName)
{
	if (NewInventoryComponent == UUtils::GetInventorySubsystem(GetWorld())->GetInventoryComponent())
	{
		TakeAllButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TakeAllButton->SetVisibility(ESlateVisibility::Visible);
	}
	
	InventoryComponent = NewInventoryComponent;
	InventoryDisplayName->SetText(FText::FromString(ContainerName));
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
		InventorySlot->SetInventoryComponent(InventoryComponent);
	}
}

void UInventoryPanel::TakeAll()
{
	if (InventoryComponent)
	{
		UUtils::GetInventorySubsystem(GetWorld())->AddItems(InventoryComponent);
	}
}
