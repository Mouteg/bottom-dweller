// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMenuWidget.generated.h"

class USimpleStatsWidget;
class UButton;
class UWidgetSwitcher;
class UInventoryUI;

UCLASS()
class BOTTOMDWELLER_API UPlayerMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> StatsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> InventoryButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventoryUI> InventoryUI;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USimpleStatsWidget> SimpleStatsWidget;

protected:
	virtual void NativeConstruct() override;

private:
	
	UFUNCTION()
	void SetStatsActive();
	UFUNCTION()
	void SetInventoryActive();
};
