// All rights reserved by Aboba Inc.


#include "JumpAbility.h"

#include "BottomDweller/Actors/Characters/BaseCharacter.h"

void UJumpAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (ABaseCharacter* Character = GetCharacterFromActorInfo())
	{
		Character->StopJumping();
		CancelAbility(Handle, ActorInfo, ActivationInfo, false);
	}
}

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (ABaseCharacter* Character = GetCharacterFromActorInfo())
	{
		Character->Jump();
	}
}

bool UJumpAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
                                      FGameplayTagContainer* OptionalRelevantTags) const
{
	if (const ABaseCharacter* Character = GetCharacterFromActorInfo(ActorInfo))
	{
		return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)
			&& Character->CanJump();
	}
	return false;
}
