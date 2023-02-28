// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquippedItemsWidget.generated.h"

enum class EItemType : uint8;
class UItemDetailsPanel;
class UItemDataAsset;
class UInventorySlotWidget;
class UInventoryComponent;
class UEquippedItemSlot;

UCLASS()
class BOTTOMDWELLER_API UEquippedItemsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquippedItemSlot> WeaponSlot;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UItemDetailsPanel> ItemDetailsPanel;

	UFUNCTION()
	void Update(UItemDataAsset* Item, EItemType GearSlot);

protected:
	void InitSlots();
	virtual void NativeConstruct() override;

private:
	TMap<EItemType, UEquippedItemSlot*> EquipSlots;
};
