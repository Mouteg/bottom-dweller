// All rights reserved by Aboba Inc.


#include "AttackAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "BottomDweller/Animation/WeaponAnimations.h"
#include "BottomDweller/DataAssets/Items/WeaponItemDataAsset.h"

void UAttackAbility::AttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//TODO Refactor
	UAnimInstance* AnimInstance = GetBottomDwellerCharacterFromActorInfo()->GetMesh()->GetAnimInstance();
	UWeaponItemDataAsset* Weapon = GetBottomDwellerCharacterFromActorInfo()->GetInventoryComponent()->GetEquipmentState().Weapon;
	if (!AnimInstance || !Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack ability, null pointer"));
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	const EWeaponType EquippedWeaponType = Weapon->WeaponType;

	if (!WeaponAnimations->WeaponTypeAnimations[EquippedWeaponType].AnimMontages[0].Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack ability AnimMontages is null"));
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	AnimInstance->Montage_Play(WeaponAnimations->WeaponTypeAnimations[EquippedWeaponType].AnimMontages[0].Get(), 1.5);
	AnimInstance->OnMontageEnded.AddDynamic(this, &UAttackAbility::AttackEnded);
}
