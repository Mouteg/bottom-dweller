// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleStatsWidget.generated.h"

struct FOnAttributeChangeData;
class UVerticalBox;
class UTextEntry;
/**
 * 
*/

USTRUCT()
struct FCompositeEntryAttributes {
	GENERATED_BODY()

	UPROPERTY()
	FString ValueAttribute;
	UPROPERTY()
	FString MaxValueAttribute;
	UPROPERTY()
	FString RegenValueAttribute;
};

UCLASS()
class BOTTOMDWELLER_API USimpleStatsWidget : public UUserWidget {
	GENERATED_BODY()

public:
	void UpdateStats(const FOnAttributeChangeData& Data);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> StatsContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTextEntry> EntryWidget;

protected:
	virtual void NativeConstruct() override;

private:
	void InitializeDelegates();
	void InitializeAttributes();
	void CreateEntries();
	void CreateOrUpdateCompositeEntry(const FCompositeEntryAttributes& CompositeAttributes, const int32 Index = 0);
	void UpdateEntry(const FString& AttributeName);

	FCompositeEntryAttributes HealthComposite = FCompositeEntryAttributes();
	FCompositeEntryAttributes StaminaComposite = FCompositeEntryAttributes();
	FCompositeEntryAttributes ManaComposite = FCompositeEntryAttributes();

	TMap<FString, int32> Attributes;
	TMap<FString, int32> AttributeToChildIndex;
	TArray<FString> DefaultAttributes;
	bool bIsInitialized = false;
};
