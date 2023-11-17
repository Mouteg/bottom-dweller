// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

class UItemDetailsPanel;
class UInventoryPanel;
class UEquippedItemsWidget;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativePreConstruct() override;
	
public:
	virtual bool Initialize() override;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UEquippedItemsWidget> EquippedItemsWidget;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UInventoryPanel> InventoryPanel;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UInventoryPanel> ContainerInventoryPanel;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UItemDetailsPanel> ItemDetailsPanel;
};
