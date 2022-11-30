// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDetailsEntry.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UItemDetailsEntry : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PropertyName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PropertyValue;

	void SetProperty(FString PropertyName, FString PropertyValue, FLinearColor Color = FLinearColor::Black) const;
};
