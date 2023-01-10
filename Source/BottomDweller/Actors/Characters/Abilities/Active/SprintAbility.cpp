// All rights reserved by Aboba Inc.


#include "SprintAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

USprintAbility::USprintAbility()
{
	SprintSpeed = 600;
}

void USprintAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GetBottomDwellerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void USprintAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	GetBottomDwellerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = GetBottomDwellerCharacterFromActorInfo()->WalkSpeed;
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USprintAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (SprintPeriodicCostEffect)
	{
		CostEffectHandle = GetAbilitySystemComponentFromActorInfo(ActorInfo)->ApplyGameplayEffectToSelf(
			SprintPeriodicCostEffect->GetDefaultObject<UGameplayEffect>(),
			1,
			MakeEffectContext(Spec.Handle, ActorInfo)
		);
	}
}

void USprintAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
	if (CostEffectHandle.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo(ActorInfo)->RemoveActiveGameplayEffect(CostEffectHandle);
	}
	
}
