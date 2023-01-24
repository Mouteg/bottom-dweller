// All rights reserved by Aboba Inc.


#include "AttackAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Animation/WeaponAnimations.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BottomDweller/Actors/Characters/Abilities/BottomDwellerAbilitySystemGlobals.h"

UAttackAbility::UAttackAbility()
{
	InPlayRate = 1.5;
	bInitialized = false;
	//Maybe instancing policy -> per actor ?
}

bool UAttackAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
                                        FGameplayTagContainer* OptionalRelevantTags) const
{
	const UWeaponItemDataAsset* Weapon = GetBottomDwellerCharacterFromActorInfo(ActorInfo)->GetInventoryComponent()->GetEquipmentState().Weapon;
	if (
		!IsValid(Weapon)
		|| !IsValid(WeaponAnimations)
		|| !WeaponAnimations->WeaponTypeAnimations.Contains(Weapon->WeaponType)
		|| !(WeaponAnimations->WeaponTypeAnimations[Weapon->WeaponType].AnimMontages.Num() > ComboCounter)
		|| !WeaponAnimations->WeaponTypeAnimations[Weapon->WeaponType].AnimMontages[ComboCounter].IsValid()
	) { return false; }
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!bInitialized)
	{
		WaitForComboOpeningTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this,
			UBottomDwellerAbilitySystemGlobals::GSGet().ComboOpeningTag
		);
		WaitForComboOpeningTask->EventReceived.AddDynamic(this, &UAttackAbility::SetComboOpening);
		WaitForComboOpeningTask->Activate();
		bInitialized = false;
	}
	
	//async task for socket tracing
	
	ApplyCost(Handle, ActorInfo, ActivationInfo);
	const UWeaponItemDataAsset* Weapon = GetBottomDwellerCharacterFromActorInfo()->GetInventoryComponent()->GetEquipmentState().Weapon;
	CurrentWeaponType = Weapon->WeaponType;
	UAnimMontage* AttackMontage = WeaponAnimations->WeaponTypeAnimations[CurrentWeaponType].AnimMontages[ComboCounter].Get();

	AttackMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		TEXT("AttackMontageTask"),
		AttackMontage,
		InPlayRate
	);
	AttackMontageTask->OnBlendOut.AddUniqueDynamic(this, &UAttackAbility::AttackMontageEnded);
	AttackMontageTask->Activate();
}

void UAttackAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (
		!bCombo
		&& ComboCounter < WeaponAnimations->WeaponTypeAnimations[CurrentWeaponType].AnimMontages.Num() - 1
		&& bComboOpening
	)
	{
		bCombo = true;
		ComboCounter += 1;
	}
}

void UAttackAbility::AttackMontageEnded()
{
	FGameplayTagContainer TargetTags;
	FGameplayTagContainer RelevantTags = FGameplayTagContainer::EmptyContainer;
	GetAbilitySystemComponentFromActorInfo()->GetOwnedGameplayTags(TargetTags);

	if (bCombo && CanActivateAbility(CurrentSpecHandle, CurrentActorInfo, &AbilityTags, &TargetTags, &RelevantTags))
	{
		ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, &CurrentEventData);
	}
	else
	{
		ComboCounter = 0;
		AttackMontageTask->OnBlendOut.RemoveAll(this);
		AttackMontageTask->OnCompleted.AddDynamic(this, &UAttackAbility::AttackCompleted);
	}
	bCombo = false;
}

void UAttackAbility::AttackCompleted()
{
	AttackMontageTask->OnCompleted.RemoveAll(this);
	AttackMontageTask->EndTask();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UAttackAbility::SetComboOpening(FGameplayEventData Payload)
{
	bComboOpening = static_cast<bool>(Payload.EventMagnitude);
}
