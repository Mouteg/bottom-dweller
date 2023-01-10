// All rights reserved by Aboba Inc.


#include "AttackComboOpening.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Actors/Characters/Abilities/GameplayTagHelpers.h"


void UAttackComboOpening::SendEvent(AActor* Owner, bool bActivated)
{
	FGameplayEventData EventData;
	EventData.Instigator = Owner->GetOwner();
	EventData.EventMagnitude = bActivated;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, UGameplayTagHelpers::GetComboOpeningTag(), EventData);
}

void UAttackComboOpening::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	SendEvent(MeshComp->GetOwner(), true);
}

void UAttackComboOpening::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	SendEvent(MeshComp->GetOwner(), false);

}
