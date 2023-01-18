// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.generated.h"

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
	class UEquippedItemsWidget* EquippedItemsWidget;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UInventoryPanel* InventoryPanel;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UItemDetailsPanel* ItemDetailsPanel;
};
