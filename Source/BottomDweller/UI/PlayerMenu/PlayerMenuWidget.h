// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMenuWidget.generated.h"

class UContainerUI;
class USimpleStatsWidget;
class UButton;
class UWidgetSwitcher;
class UInventoryUI;

UENUM(BlueprintType)
enum class EPlayerMenuScreen : uint8
{
	Inventory,
	Stats,
	Container,
};

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
	
	UFUNCTION()
	void SetActiveScreen(EPlayerMenuScreen Screen);
	
	virtual void SetVisibility(ESlateVisibility InVisibility) override;

protected:
	virtual void NativeConstruct() override;

private:

	TMap<EPlayerMenuScreen, TObjectPtr<UUserWidget>> WidgetMap;
	
	UFUNCTION()
	void SetStatsActive();
	UFUNCTION()
	void SetInventoryActive();

};
