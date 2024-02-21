// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "DamageCalculation.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UDamageCalculation : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()

public:
	UDamageCalculation();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition BluntResistanceDef;
	FGameplayEffectAttributeCaptureDefinition SlashingResistanceDef;
	FGameplayEffectAttributeCaptureDefinition PiercingResistanceDef;

	FGameplayEffectAttributeCaptureDefinition BluntDamageDef;
	FGameplayEffectAttributeCaptureDefinition SlashingDamageDef;
	FGameplayEffectAttributeCaptureDefinition PiercingDamageDef;
};
