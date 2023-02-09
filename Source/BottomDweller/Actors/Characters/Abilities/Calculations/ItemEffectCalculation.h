// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ItemEffectCalculation.generated.h"

// typedef TFunction<void(EGameplayModEvaluationChannel, EGameplayModOp::Type, const FAggregatorMod&)> FEvaluateFunction;

//------------------------------NOT USED------------------------------\\

UCLASS()
class BOTTOMDWELLER_API UItemEffectCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UItemEffectCalculation();

	void AddOutputModifier(FProperty* Property, const float Magnitude) const;

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

private:
	mutable FGameplayEffectCustomExecutionOutput* CurrentOutExecutionOutput;
	
};
