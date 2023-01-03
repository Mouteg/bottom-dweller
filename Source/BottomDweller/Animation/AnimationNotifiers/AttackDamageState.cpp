// All rights reserved by Aboba Inc.


#include "AttackDamageState.h"

#include "BottomDweller/Actors/Characters/MeleeAttacker.h"

void UAttackDamageState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (IMeleeAttacker* MeleeAttacker = Cast<IMeleeAttacker>(MeshComp->GetOwner()))
	{
		MeleeAttacker->EnableWeaponCollision();
	}
}

void UAttackDamageState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (IMeleeAttacker* MeleeAttacker = Cast<IMeleeAttacker>(MeshComp->GetOwner()))
	{
		MeleeAttacker->DisableWeaponCollision();
	}
}
