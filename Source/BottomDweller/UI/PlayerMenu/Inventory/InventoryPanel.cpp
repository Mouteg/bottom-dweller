// All rights reserved by Aboba Inc.


#include "InventoryPanel.h"
#include "InventorySlotWidget.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

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
	
	if (const ABottomDwellerCharacter* Character = Cast<ABottomDwellerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		InventoryComponent = Character->GetInventoryComponent();
		InventoryComponent->OnChange.AddUniqueDynamic(this, &UInventoryPanel::Refresh);
	}
	Refresh();
}

void UInventoryPanel::Refresh()
{
	if (!InventoryComponent || !ItemDetailsPanel) return;

	InventorySlots->ClearChildren();
	ItemDetailsPanel->SetVisibility(ESlateVisibility::Hidden);

	for (TTuple<TSoftObjectPtr<UItemDataAsset>, int> Pair : InventoryComponent->GetInventoryContent())
	{
		UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, SlotWidget);
		InventorySlots->AddChild(InventorySlot);
		InventorySlot->SetItem(Pair.Key.Get(), Pair.Value);
		InventorySlot->ItemDetailsPanel = ItemDetailsPanel;
	}
}
