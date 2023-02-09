// All rights reserved by Aboba Inc.


#include "AttackAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Animation/WeaponAnimations.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BottomDweller/Actors/Characters/BaseAttributeSet.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/Actors/Components/WeaponComponent.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/ComponentProviderSupport.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	if (!ActorInfo->AvatarActor.Get() || !ActorInfo->AvatarActor->Implements<UComponentProviderSupport>())
	{
		return false;
	}

	const UWeaponItemDataAsset* Weapon = IComponentProviderSupport::Execute_GetInventoryComponent(ActorInfo->AvatarActor.Get())->GetEquipmentState().Weapon;

	return
		!IComponentProviderSupport::Execute_GetPawnMovementComponent(ActorInfo->AvatarActor.Get())->IsFalling()
		&& CheckAnimations(Weapon)
		&& Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!bInitialized)
	{
		CreateComboOpeningTask();
	}

	ApplyCost(Handle, ActorInfo, ActivationInfo);
	const UWeaponItemDataAsset* Weapon = IComponentProviderSupport::Execute_GetInventoryComponent(GetOwningActorFromActorInfo())->GetEquipmentState().Weapon;
	CurrentWeaponType = Weapon->WeaponType;
	GetBottomDwellerCharacterFromActorInfo()->WeaponComponent->OnHit.AddUniqueDynamic(this, &ThisClass::OnActorHit);
	UAnimMontage* AttackMontage = WeaponAnimations->WeaponTypeAnimations[CurrentWeaponType].AnimMontages[ComboCounter].Get();

	CreateAttackMontageTask(AttackMontage);
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
	bComboOpening = Payload.EventMagnitude > 0;
}

void UAttackAbility::OnActorHit(FHitResult HitResult)
{
	const AActor* Actor = HitResult.GetActor();
	if (Actor->IsA(AStaticMeshActor::StaticClass()))
	{
		//Play cancel montage
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
		UE_LOG(LogTemp, Warning, TEXT("Static mesh hit - canceling attack"));
	}

	if (Actor->IsA(ABaseCharacter::StaticClass()))
	{
		float Damage = UBaseAttributeSet::GetBluntDamageValue(GetBaseCharacterFromActorInfo())
			+ UBaseAttributeSet::GetSlashingDamageValue(GetBaseCharacterFromActorInfo())
			+ UBaseAttributeSet::GetPiercingDamageValue(GetBaseCharacterFromActorInfo());
		//deal damage
	}
}

bool UAttackAbility::CheckAnimations(const UWeaponItemDataAsset* Weapon) const
{
	return
		IsValid(Weapon)
		&& IsValid(WeaponAnimations)
		&& WeaponAnimations->WeaponTypeAnimations.Contains(Weapon->WeaponType)
		&& (WeaponAnimations->WeaponTypeAnimations[Weapon->WeaponType].AnimMontages.Num() > ComboCounter)
		&& WeaponAnimations->WeaponTypeAnimations[Weapon->WeaponType].AnimMontages[ComboCounter].IsValid();
}


void UAttackAbility::CreateComboOpeningTask()
{
	WaitForComboOpeningTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		Tag_Event_Attack_ComboOpening
	);
	WaitForComboOpeningTask->EventReceived.AddDynamic(this, &ThisClass::SetComboOpening);
	WaitForComboOpeningTask->Activate();
	bInitialized = false;
}

void UAttackAbility::CreateAttackMontageTask(UAnimMontage* AttackMontage)
{
	AttackMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		TEXT("AttackMontageTask"),
		AttackMontage,
		InPlayRate
	);
	AttackMontageTask->OnBlendOut.AddUniqueDynamic(this, &ThisClass::AttackMontageEnded);
	AttackMontageTask->OnCompleted.AddDynamic(this, &ThisClass::AttackCompleted);
	AttackMontageTask->Activate();
}
