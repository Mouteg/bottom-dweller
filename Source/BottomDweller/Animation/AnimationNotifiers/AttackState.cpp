// All rights reserved by Aboba Inc.


#include "AttackState.h"

#include "BottomDweller/Actors/Characters/MeleeAttacker.h"

void UAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                               const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (IMeleeAttacker* MeleeAttacker = Cast<IMeleeAttacker>(MeshComp->GetOwner()))
	{
		MeleeAttacker->EnableWeaponCollision();
	}
}

void UAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (IMeleeAttacker* MeleeAttacker = Cast<IMeleeAttacker>(MeshComp->GetOwner()))
	{
		MeleeAttacker->DisableWeaponCollision();
	}
}
