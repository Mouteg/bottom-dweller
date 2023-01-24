// All rights reserved by Aboba Inc.


#include "InteractAbility.h"

#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InteractionComponent.h"

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
		Character->GetInteractionComponent()->Interact(Character);
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
