// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "InventorySlotWidget.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHover, UItemDataAsset*, Item);
DECLARE_DYNAMIC_DELEGATE(FOnUnHover);

UCLASS()
class BOTTOMDWELLER_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	UItemDataAsset* Item;

	UPROPERTY()
	int32 Quantity;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* Thumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityText;

	UPROPERTY()
	FOnHover OnHover;
	
	UPROPERTY()
	FOnUnHover OnUnHover;

	virtual bool Initialize() override;

	void SetItem(UItemDataAsset* InventoryItem, int32 ItemQuantity);

protected:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
