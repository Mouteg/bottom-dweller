﻿// All rights reserved by Aboba Inc.


#include "InventorySlotWidget.h"

#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "GameFramework/Character.h"

bool UInventorySlotWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	DoubleClickEventTag = Tag_Event_UseItem;

	return bSuccess;
}

void UInventorySlotWidget::SetItem(UItemDataAsset* InventoryItem, int32 ItemQuantity)
{
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
	QuantityText->SetText(FText::AsNumber(Quantity));
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
		FGameplayEventData EventData;
		EventData.Instigator = GetOwningPlayer();
		EventData.OptionalObject = Item;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPlayer()->GetCharacter(), DoubleClickEventTag, EventData);
	}
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}
