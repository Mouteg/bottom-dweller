// All rights reserved by Aboba Inc.


#include "InventorySlotWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

bool UInventorySlotWidget::Initialize()
{
	const bool bSuccess = Super::Initialize();
	if (!bSuccess) return false;
	return bSuccess;
}

void UInventorySlotWidget::SetItem(UItemDataAsset* InventoryItem, int32 ItemQuantity)
{
	Item = InventoryItem;
	Quantity = ItemQuantity;
	//TODO Remove sync load
	if (UTexture2D* ItemThumbnail = Item->Thumbnail.LoadSynchronous())
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
	Thumbnail->SetRenderOpacity(0.5);
	OnHover.Execute(Item);
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	Thumbnail->SetRenderOpacity(1);
	OnUnHover.Execute();
}
