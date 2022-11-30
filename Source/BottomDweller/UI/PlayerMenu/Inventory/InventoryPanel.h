// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotWidget.h"
#include "ItemDetailsPanel.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "InventoryPanel.generated.h"

UCLASS()
class BOTTOMDWELLER_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void OnHover(UItemDataAsset* Item);
	
	UFUNCTION()
	void OnUnHover();
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWrapBox* InventorySlots;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* InventoryDisplayName;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite)
	UItemDetailsPanel* ItemDetailsPanel;

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetItemDetailsPanel(UItemDetailsPanel* Panel)
	{
		this->ItemDetailsPanel = Panel;
	}

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotWidget> SlotWidget;

	virtual bool Initialize() override;

	UFUNCTION()
	void Refresh();
protected:
	virtual void NativeConstruct() override;
	
};
