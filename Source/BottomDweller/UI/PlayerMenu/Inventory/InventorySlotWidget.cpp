// All rights reserved by Aboba Inc.


#include "InventorySlotWidget.h"

#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "ItemDetailsPanel.h"
#include "BottomDweller/Util/UUtils.h"

bool UInventorySlotWidget::Initialize() {
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) {
		return false;
	}

	return bSuccess;
}

void UInventorySlotWidget::InitSlot(UItemDetailsPanel* DetailsPanel, UItemDataAsset* InventoryItem, const int32 ItemQuantity) {
	ItemDetailsPanel = DetailsPanel;
	Item = InventoryItem;
	Quantity = ItemQuantity;

	if (IsValid(Item) && Item->Thumbnail.Get()) {
		UTexture2D* ItemThumbnail = Item->Thumbnail.Get();
		Thumbnail->SetBrushFromTexture(ItemThumbnail);
	} else {
		Thumbnail->SetBrushColor(FLinearColor::White);
	}

	if (Quantity > 1) {
		QuantityText->SetText(FText::AsNumber(Quantity));
	} else {
		QuantityText->SetText(FText::FromString(""));
	}
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (ItemDetailsPanel && Item) {
		ItemDetailsPanel->LoadDetails(Item);
		ItemDetailsPanel->SetVisibility(ESlateVisibility::Visible);
		Thumbnail->SetRenderOpacity(0.5);
	}
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseLeave(InMouseEvent);
	if (ItemDetailsPanel) {
		ItemDetailsPanel->SetVisibility(ESlateVisibility::Hidden);
		Thumbnail->SetRenderOpacity(1);
	}
}

FReply UInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	if (Item && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
		// If we clicked on container slot or player INV slot
		if (UPlayerInventoryController* PlayerInventoryController = UUtils::GetInventorySubsystem(GetWorld());
			PlayerInventoryController->GetInventoryComponent() == InventoryComponent
		) {
			PlayerInventoryController->UseItem(Item);
		} else {
			const int32 ItemsAdded = PlayerInventoryController->AddItem(Item, Quantity);
			InventoryComponent->RemoveItem(Item, ItemsAdded);
		}
	}
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

FReply UInventorySlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	if (Item && InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton) {
		if (UPlayerInventoryController* PlayerInventoryController = UUtils::GetInventorySubsystem(GetWorld());
			PlayerInventoryController->GetInventoryComponent() != InventoryComponent
		) {
			PlayerInventoryController->AddItem(Item, 1);
			InventoryComponent->RemoveItem(Item, 1);
		}
	}
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}
