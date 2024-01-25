// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/Actors/Components/EquipmentComponent.h"
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

	UFUNCTION()
	void Update(UItemDataAsset* Item, EItemType GearSlot);
	
	void SetItemDetailsPanel(const TObjectPtr<UItemDetailsPanel> DetailsPanel)
	{
		ItemDetailsPanel = DetailsPanel;
	}
protected:
	
	UPROPERTY()
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEquippedItemSlot> WeaponSlot;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UItemDetailsPanel> ItemDetailsPanel;
	void InitSlots();
	
	virtual void NativeConstruct() override;

private:
	TMap<EItemType, UEquippedItemSlot*> EquipSlots;
};
