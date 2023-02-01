// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleStatsWidget.generated.h"

struct FOnAttributeChangeData;
class UVerticalBox;
class UItemDetailsEntry;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API USimpleStatsWidget : public UUserWidget
{
	GENERATED_BODY()

	void InitDelegates();

	TMap<FString, float> Attributes;

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateStats(const FOnAttributeChangeData& Data);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* StatsContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UItemDetailsEntry> EntryWidget;
};
