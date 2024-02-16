﻿// All rights reserved by Aboba Inc.


#include "InventorySlotWidget.h"

#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Util/UUtils.h"

bool UInventorySlotWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;

	return bSuccess;
}

void UInventorySlotWidget::InitSlot(UItemDetailsPanel* DetailsPanel, UItemDataAsset* InventoryItem, const int32 ItemQuantity)
{
	ItemDetailsPanel = DetailsPanel;
	Item = InventoryItem;
	Quantity = ItemQuantity;

	if (UTexture2D* ItemThumbnail = Item->Thumbnail.Get())
	{
		Thumbnail->SetBrushFromTexture(ItemThumbnail);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant load item thumbnail"));
	}

	if (Quantity > 1)
	{
		QuantityText->SetText(FText::AsNumber(Quantity));
	}
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (ItemDetailsPanel && Item)
	{
		ItemDetailsPanel->LoadDetails(Item);
		ItemDetailsPanel->SetVisibility(ESlateVisibility::Visible);
		Thumbnail->SetRenderOpacity(0.5);
	}
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (ItemDetailsPanel)
	{
		ItemDetailsPanel->SetVisibility(ESlateVisibility::Hidden);
		Thumbnail->SetRenderOpacity(1);
	}
}

FReply UInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (Item)
	{
		UPlayerInventoryController* PlayerInventoryController = UUtils::GetInventorySubsystem(GetWorld());
		// If we clicked on container slot or player INV slot
		if (PlayerInventoryController->GetInventoryComponent() == InventoryComponent)
		{
			PlayerInventoryController->UseItem(Item);
		}
		else
		{
			PlayerInventoryController->AddItem(Item, Quantity);
			InventoryComponent->RemoveItem(Item, Quantity);
		}
	}
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}
