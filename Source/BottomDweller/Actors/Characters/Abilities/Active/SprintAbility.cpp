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
