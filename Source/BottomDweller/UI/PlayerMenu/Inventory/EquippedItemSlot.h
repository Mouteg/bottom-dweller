// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidget.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"
#include "EquippedItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UEquippedItemSlot : public UInventorySlotWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	EGearSlots EquipmentSlot;
	
protected:
	
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
