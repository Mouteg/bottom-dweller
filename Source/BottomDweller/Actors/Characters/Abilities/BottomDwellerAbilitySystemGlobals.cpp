// All rights reserved by Aboba Inc.


#include "BottomDwellerAbilitySystemGlobals.h"

UBottomDwellerAbilitySystemGlobals::UBottomDwellerAbilitySystemGlobals()
{
}

FGameplayEffectContext* UBottomDwellerAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FCustomGameplayEffectContext();
}
