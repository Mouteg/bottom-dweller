// All rights reserved by Aboba Inc.


#include "AbilityBasedCostCalculation.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseGameplayAbility.h"

float UAbilityBasedCostCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UBaseGameplayAbility* Ability = Cast<UBaseGameplayAbility>(Spec.GetContext().GetAbility());
	if (!Ability)
	{
		return 0;
	}
	return -Ability->Cost;
}
