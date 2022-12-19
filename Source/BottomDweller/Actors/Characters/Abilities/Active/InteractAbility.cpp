// All rights reserved by Aboba Inc.


#include "InteractAbility.h"

#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"

void UInteractAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData
)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (ABottomDwellerCharacter* Character = GetBottomDwellerCharacterFromActorInfo())
	{
		Character->Interact();
	}
}
