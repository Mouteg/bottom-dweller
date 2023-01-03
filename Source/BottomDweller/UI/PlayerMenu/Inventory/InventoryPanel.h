// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.generated.h"

class UInventorySlotWidget;
class UItemDetailsPanel;
class UInventoryComponent;
class UItemDataAsset;

UCLASS()
class BOTTOMDWELLER_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* InventorySlots;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InventoryDisplayName;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite)
	UItemDetailsPanel* ItemDetailsPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotWidget> SlotWidget;

	virtual bool Initialize() override;

	UFUNCTION()
	void Refresh();
	
protected:
	virtual void NativeConstruct() override;
};
