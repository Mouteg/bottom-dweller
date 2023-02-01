// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMenuWidget.generated.h"

class USimpleStatsWidget;
class UButton;
class UWidgetSwitcher;
class UInventoryUI;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UPlayerMenuWidget : public UUserWidget
{
	GENERATED_BODY()

    UFUNCTION()
	void SetStatsActive();
	UFUNCTION()
	void SetInventoryActive();

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* StatsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* InventoryButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UInventoryUI* InventoryUI;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USimpleStatsWidget* SimpleStatsWidget;

protected:
	virtual void NativeConstruct() override;
	
};
