﻿// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseGameplayAbility.h"
#include "AttackAbility.generated.h"

UCLASS()
class BOTTOMDWELLER_API UAttackAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class UWeaponAnimations* WeaponAnimations;

	UFUNCTION()
	void AttackEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
};
