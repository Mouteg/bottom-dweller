// All rights reserved by Aboba Inc.


#include "AttackState.h"

#include "BottomDweller/Actors/Characters/MeleeAttacker.h"

void UAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                               const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp->GetOwner()->Implements<UMeleeAttacker>())
	{
		IMeleeAttacker::Execute_BeginAttack(MeshComp->GetOwner());
	}
}

void UAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp->GetOwner()->Implements<UMeleeAttacker>())
	{
		IMeleeAttacker::Execute_EndAttack(MeshComp->GetOwner());
	}
}
