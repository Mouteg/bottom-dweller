// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextEntry.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UTextEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PropertyName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PropertyValue;

	void SetProperty(FString PropertyName, FString PropertyValue, FLinearColor Color = FLinearColor::Black);
	void SetValue(FString PropertyValue);
	void SetName(FString PropertyName);
	void SetColor(FLinearColor Color = FLinearColor::Black);
};
