// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventoryPanel.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class BOTTOMDWELLER_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	UInventoryPanel* Owner;
	
public:
	UPROPERTY(BlueprintReadWrite)
	UItemDataAsset* Item;

	UPROPERTY()
	int32 Quantity;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* Thumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityText;

	virtual bool Initialize() override;

	void SetItem(UItemDataAsset* InventoryItem, int32 ItemQuantity);
	void SetOwner(UInventoryPanel* OwnerWidget);

protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
