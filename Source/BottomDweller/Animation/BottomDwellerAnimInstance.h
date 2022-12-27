// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "BottomDwellerAnimInstance.generated.h"

class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UBottomDwellerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* ASC);
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameplayTags")
	FGameplayTagBlueprintPropertyMap GameplayTagPropertyMap;
};
