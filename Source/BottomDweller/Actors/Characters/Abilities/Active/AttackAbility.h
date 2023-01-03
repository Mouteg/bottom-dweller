// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseGameplayAbility.h"
#include "AttackAbility.generated.h"

enum class EWeaponType : uint8;

UCLASS()
class BOTTOMDWELLER_API UAttackAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

	bool bCombo;
	int32 ComboCounter;

	EWeaponType CurrentWeaponType;
	
	UPROPERTY(EditDefaultsOnly)
	class UWeaponAnimations* WeaponAnimations;

	UFUNCTION()
	void AttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
public:

	UAttackAbility();
	
	UPROPERTY(EditAnywhere)
	float InPlayRate;
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
	
};
