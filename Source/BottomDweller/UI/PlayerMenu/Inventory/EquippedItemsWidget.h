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
	UInventoryComponent* InventoryComponent;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEquippedItemSlot* WeaponSlot;
	
	UPROPERTY(BlueprintReadWrite)
	UItemDetailsPanel* ItemDetailsPanel;
	
	UFUNCTION()
	void Update(UItemDataAsset* Item, EGearSlots GearSlot);
	
protected:
	void InitSlots();
	virtual void NativeConstruct() override;
};
