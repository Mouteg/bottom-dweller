// All rights reserved by Aboba Inc.


#include "BaseGameplayAbility.h"

#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"


UAbilitySystemComponent* UBaseGameplayAbility::GetAbilitySystemComponentFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo && Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()))
	{
		return Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get())->GetAbilitySystemComponent();
	}
	return (CurrentActorInfo ? Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor.Get())->GetAbilitySystemComponent() : nullptr);
}

ABottomDwellerPlayerController* UBaseGameplayAbility::GetPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ABottomDwellerPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

ABaseCharacter* UBaseGameplayAbility::GetCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo)
	{
		return (ActorInfo ? Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()) : nullptr);
	}
	return (CurrentActorInfo ? Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

ABottomDwellerCharacter* UBaseGameplayAbility::GetBottomDwellerCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo)
	{
		return (ActorInfo ? Cast<ABottomDwellerCharacter>(ActorInfo->AvatarActor.Get()) : nullptr);
	}
	return (CurrentActorInfo ? Cast<ABottomDwellerCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}
