// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "AbilityBasedCostCalculation.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UAbilityBasedCostCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};
