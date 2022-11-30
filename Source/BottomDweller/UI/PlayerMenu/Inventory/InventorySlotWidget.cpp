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
	if (!Item->Thumbnail.Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant load item thumbnail"));
	}
	Thumbnail->SetBrushFromTexture(Item->Thumbnail.Get());
	QuantityText->SetText(FText::AsNumber(Quantity));
}

void UInventorySlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	Thumbnail->SetRenderOpacity(0.5);
	OnHover.Execute(Item);
	//Set item details panel visible
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	Thumbnail->SetRenderOpacity(1);
	OnUnHover.Execute();
	//Set item details panel invisible
}
