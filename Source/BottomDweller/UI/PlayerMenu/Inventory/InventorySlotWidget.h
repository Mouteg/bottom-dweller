// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InventoryPanel.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class BOTTOMDWELLER_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DoubleClickEventTag;
	
	UPROPERTY(BlueprintReadWrite)
	UItemDataAsset* Item;

	UPROPERTY()
	int32 Quantity;
	
	UPROPERTY()
	UItemDetailsPanel* ItemDetailsPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* Thumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityText;

	virtual bool Initialize() override;
	
	void SetItem(UItemDataAsset* InventoryItem, int32 ItemQuantity = 1);

protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
