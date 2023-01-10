// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameplayTagHelpers.generated.h"

UCLASS()
class BOTTOMDWELLER_API UGameplayTagHelpers : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	static FGameplayTag GetComboOpeningTag();
	
	UFUNCTION()
	static FGameplayTag GetUseItemTag();
};
