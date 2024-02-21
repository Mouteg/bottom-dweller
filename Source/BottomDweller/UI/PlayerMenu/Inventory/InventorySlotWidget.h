// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventoryPanel.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/DataAssets/Items/GearItemDataAsset.h"
#include "InventorySlotWidget.generated.h"

class UBorder;

UCLASS()
class BOTTOMDWELLER_API UInventorySlotWidget : public UUserWidget {
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetInventoryComponent(const TObjectPtr<UInventoryComponent>& OwnerInventoryComponent) {
		InventoryComponent = OwnerInventoryComponent;
	}

	void InitSlot(UItemDetailsPanel* ItemDetailsPanel, UItemDataAsset* InventoryItem, int32 ItemQuantity = 1);

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UItemDataAsset> Item;

	UPROPERTY()
	int32 Quantity;

	UPROPERTY()
	TObjectPtr<UItemDetailsPanel> ItemDetailsPanel;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> Thumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
