// All rights reserved by Aboba Inc.


#include "AttackAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "BottomDweller/Animation/WeaponAnimations.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"

UAttackAbility::UAttackAbility()
{
	InPlayRate = 1.5;
}

bool UAttackAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
                                        FGameplayTagContainer* OptionalRelevantTags) const
{
	const UWeaponItemDataAsset* Weapon = GetBottomDwellerCharacterFromActorInfo(ActorInfo)->GetInventoryComponent()->GetEquipmentState().Weapon;
	if (
		!IsValid(Weapon)
		|| !IsValid(GetBottomDwellerCharacterFromActorInfo(ActorInfo)->GetMesh()->GetAnimInstance())
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
	//TODO Refactor

	UAnimInstance* AnimInstance = GetBottomDwellerCharacterFromActorInfo()->GetMesh()->GetAnimInstance();
	const UWeaponItemDataAsset* Weapon = GetBottomDwellerCharacterFromActorInfo()->GetInventoryComponent()->GetEquipmentState().Weapon;
	CurrentWeaponType = Weapon->WeaponType;
	const TSoftObjectPtr<UAnimMontage> AttackMontage = WeaponAnimations->WeaponTypeAnimations[Weapon->WeaponType].AnimMontages[ComboCounter];
	
	AnimInstance->Montage_Play(AttackMontage.Get(), InPlayRate);
	AnimInstance->OnMontageEnded.AddUniqueDynamic(this, &UAttackAbility::AttackMontageEnded);
}

void UAttackAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								  const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (
		!bCombo
		&& ComboCounter < WeaponAnimations->WeaponTypeAnimations[CurrentWeaponType].AnimMontages.Num() - 1
		//Change tag to ComboTimeframe something
		&& GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("Event.Attack")))
	)
	{
		bCombo = true;
		ComboCounter += 1;
	}
}

void UAttackAbility::AttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
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
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	}
	bCombo = false;
}