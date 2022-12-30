// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
// #include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "InventoryPanel.generated.h"

class UInventorySlotWidget;
class UItemDetailsPanel;
class UInventoryComponent;
class UItemDataAsset;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHover, UItemDataAsset*, Item);
DECLARE_DYNAMIC_DELEGATE(FOnUnHover);

UCLASS()
class BOTTOMDWELLER_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void Hover(UItemDataAsset* Item);
	
	UFUNCTION()
	void UnHover();
	
public:
	
	UPROPERTY()
	FOnHover OnHover;
	
	UPROPERTY()
	FOnUnHover OnUnHover;
	
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
