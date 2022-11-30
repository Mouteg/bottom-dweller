// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "UObject/Object.h"
#include "UseItemAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UUseItemAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
