// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidget.h"
#include "EquippedItemSlot.generated.h"

enum class EItemType : uint8;

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UEquippedItemSlot : public UInventorySlotWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	EItemType EquipmentSlot;

protected:
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
