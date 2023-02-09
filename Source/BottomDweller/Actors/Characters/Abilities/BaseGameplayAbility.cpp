// All rights reserved by Aboba Inc.


#include "BaseGameplayAbility.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/ComponentProviderSupport.h"
#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"


UAbilitySystemComponent* UBaseGameplayAbility::GetAbilitySystemComponentFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo && ActorInfo->AvatarActor.Get()->Implements<UComponentProviderSupport>())
	{
		return IComponentProviderSupport::Execute_GetASCComponent(ActorInfo->AvatarActor.Get());
	}
	return (CurrentActorInfo ? IComponentProviderSupport::Execute_GetASCComponent(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

ABottomDwellerPlayerController* UBaseGameplayAbility::GetPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ABottomDwellerPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

ACharacter* UBaseGameplayAbility::GetCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo)
	{
		return (ActorInfo ? Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()) : nullptr);
	}
	return (CurrentActorInfo ? Cast<ACharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

ABottomDwellerCharacter* UBaseGameplayAbility::GetBottomDwellerCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo)
	{
		return (ActorInfo ? Cast<ABottomDwellerCharacter>(ActorInfo->AvatarActor.Get()) : nullptr);
	}
	return (CurrentActorInfo ? Cast<ABottomDwellerCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

ABaseCharacter* UBaseGameplayAbility::GetBaseCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo)
	{
		return (ActorInfo ? Cast<ABaseCharacter>(ActorInfo->AvatarActor.Get()) : nullptr);
	}
	return (CurrentActorInfo ? Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}
