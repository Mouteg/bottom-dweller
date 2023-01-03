// All rights reserved by Aboba Inc.


#include "AttackComboOpening.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"

UAttackComboOpening::UAttackComboOpening()
{
	AttackComboOpeningEventTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.ComboOpening"));
}

void UAttackComboOpening::SendEvent(AActor* Owner, bool bActivated)
{
	FGameplayEventData EventData;
	EventData.Instigator = Owner->GetOwner();
	EventData.EventMagnitude = bActivated;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, AttackComboOpeningEventTag, EventData);
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
