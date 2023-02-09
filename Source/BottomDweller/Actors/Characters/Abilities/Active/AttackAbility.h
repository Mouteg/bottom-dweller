// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseGameplayAbility.h"
#include "AttackAbility.generated.h"

class UWeaponItemDataAsset;
class UWeaponAnimations;
class UAbilityTask_WaitGameplayEvent;
class UAbilityTask_PlayMontageAndWait;
enum class EWeaponType : uint8;

UCLASS()
class BOTTOMDWELLER_API UAttackAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UAttackAbility();

	UPROPERTY(EditAnywhere)
	float InPlayRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffect;

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                          const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                                const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	                                FGameplayTagContainer* OptionalRelevantTags) const override;

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

private:
	bool bInitialized;
	bool bCombo;
	bool bComboOpening;
	int32 ComboCounter;

	EWeaponType CurrentWeaponType;

	bool CheckAnimations(const UWeaponItemDataAsset* Weapon) const;
	void CreateComboOpeningTask();
	void CreateAttackMontageTask(UAnimMontage* AttackMontage);
	void DealDamage(const AActor* Target);

	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> AttackMontageTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitGameplayEvent> WaitForComboOpeningTask;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWeaponAnimations> WeaponAnimations;

	UFUNCTION()
	void AttackMontageEnded();
	UFUNCTION()
	void AttackCompleted();
	UFUNCTION()
	void SetComboOpening(FGameplayEventData Payload);
	UFUNCTION()
	void OnActorHit(FHitResult HitResult);
};
