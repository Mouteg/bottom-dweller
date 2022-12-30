// All rights reserved by Aboba Inc.


#include "InventoryPanel.h"
#include "InventorySlotWidget.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
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
		InventoryComponent->OnChange.AddDynamic(this, &UInventoryPanel::Refresh);
	}
	Refresh();
	
	OnHover.BindUFunction(this, FName("Hover"));
	OnUnHover.BindUFunction(this, FName("UnHover"));
}

void UInventoryPanel::Refresh()
{
	if (!InventoryComponent) return;

	InventorySlots->ClearChildren();
	UnHover();

	for (TTuple<TSoftObjectPtr<UItemDataAsset>, int> Pair : InventoryComponent->GetInventoryContent())
	{
		UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, SlotWidget);
		InventorySlots->AddChild(InventorySlot);
		InventorySlot->SetOwner(this);
		InventorySlot->SetItem(Pair.Key.Get(), Pair.Value);
	}
}

void UInventoryPanel::Hover(UItemDataAsset* Item)
{
	if (!ItemDetailsPanel) return;
	ItemDetailsPanel->LoadDetails(Item);
	ItemDetailsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryPanel::UnHover()
{
	if (!ItemDetailsPanel) return;
	ItemDetailsPanel->SetVisibility(ESlateVisibility::Hidden);
}
