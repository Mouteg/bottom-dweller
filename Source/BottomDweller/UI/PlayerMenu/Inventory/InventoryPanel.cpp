// All rights reserved by Aboba Inc.


#include "InventoryPanel.h"
#include "InventorySlotWidget.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
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

void UInventoryPanel::Refresh()
{
	if (!InventoryComponent) return;

	InventorySlots->ClearChildren();

	for (TTuple<TSoftObjectPtr<UItemDataAsset>, int> Pair : InventoryComponent->InventoryContent)
	{
		UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, SlotWidget);
		InventorySlot->OnHover.BindUFunction(this, FName("OnHover"));
		InventorySlot->OnUnHover.BindUFunction(this, FName("OnUnHover"));
		//TODO Does unbind automatically ?

		InventorySlots->AddChild(InventorySlot);
		InventorySlot->SetItem(Pair.Key.Get(), Pair.Value);
	}
}

void UInventoryPanel::OnHover(UItemDataAsset* Item)
{
	if (!ItemDetailsPanel) return;
	ItemDetailsPanel->LoadDetails(Item);
	ItemDetailsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryPanel::OnUnHover()
{
	if (!ItemDetailsPanel) return;
	ItemDetailsPanel->SetVisibility(ESlateVisibility::Hidden);
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
}
