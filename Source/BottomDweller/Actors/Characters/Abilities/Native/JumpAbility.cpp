// All rights reserved by Aboba Inc.


#include "JumpAbility.h"

#include "BottomDweller/Actors/Characters/BaseCharacter.h"

void UJumpAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	if (ABaseCharacter* Character = GetCharacterFromActorInfo())
	{
		Character->Jump();
	}
}

void UJumpAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	if (ABaseCharacter* Character = GetCharacterFromActorInfo())
	{
		Character->StopJumping();
	}
}
