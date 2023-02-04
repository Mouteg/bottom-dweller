// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"
#include "EquippedItemsWidget.generated.h"

class UItemDetailsPanel;
class UItemDataAsset;
class UInventorySlotWidget;
class UInventoryComponent;
class UEquippedItemSlot;

UCLASS()
class BOTTOMDWELLER_API UEquippedItemsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	TMap<EGearSlots, UEquippedItemSlot*> EquipSlots;

public:
	
	virtual bool Initialize() override;
	
	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquippedItemSlot> WeaponSlot;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UItemDetailsPanel> ItemDetailsPanel;
	
	UFUNCTION()
	void Update(UItemDataAsset* Item, EGearSlots GearSlot);
	
protected:
	void InitSlots();
	virtual void NativeConstruct() override;
};
