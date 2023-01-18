// All rights reserved by Aboba Inc.


#include "AttackDamageState.h"

#include "BottomDweller/Actors/Characters/MeleeAttacker.h"

void UAttackDamageState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp->GetOwner()->Implements<UMeleeAttacker>())
	{
		IMeleeAttacker::Execute_EnableWeaponCollision(MeshComp->GetOwner());
	}
}

void UAttackDamageState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp->GetOwner()->Implements<UMeleeAttacker>())
	{
		IMeleeAttacker::Execute_DisableWeaponCollision(MeshComp->GetOwner());
	}
}
