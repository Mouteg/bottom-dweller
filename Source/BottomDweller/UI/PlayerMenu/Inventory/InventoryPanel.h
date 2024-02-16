// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

class UTextBlock;
class UWrapBox;
class UInventorySlotWidget;
class UItemDetailsPanel;
class UInventoryComponent;
class UItemDataAsset;

UCLASS()
class BOTTOMDWELLER_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION()
	void Refresh();

	void SetInventory(UInventoryComponent* NewInventoryComponent, const FString& ContainerName = "Inventory");

	void SetItemDetailsPanel(const TObjectPtr<UItemDetailsPanel> DetailsPanel)
	{
		ItemDetailsPanel = DetailsPanel;
	}

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> InventorySlots;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> InventoryDisplayName;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UItemDetailsPanel> ItemDetailsPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotWidget> SlotWidget;

	virtual void NativeConstruct() override;
};
