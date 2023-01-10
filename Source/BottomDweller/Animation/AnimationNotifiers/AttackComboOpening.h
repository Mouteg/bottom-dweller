// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackComboOpening.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UAttackComboOpening : public UAnimNotifyState
{
	GENERATED_BODY()

	void SendEvent(AActor* Owner, bool bActivated);

public:

	UPROPERTY(EditAnywhere)
	FGameplayTag AttackComboOpeningEventTag;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
		const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
