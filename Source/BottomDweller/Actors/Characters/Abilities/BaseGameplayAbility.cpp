// All rights reserved by Aboba Inc.


#include "BaseGameplayAbility.h"

#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"


ABottomDwellerPlayerController* UBaseGameplayAbility::GetPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ABottomDwellerPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

ABaseCharacter* UBaseGameplayAbility::GetCharacterFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ABaseCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}