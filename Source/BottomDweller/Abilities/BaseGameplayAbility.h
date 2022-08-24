// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BottomDweller/Data/BottomDwellerData.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseGameplayAbility();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	EInputAbilityId AbilityInputId{EInputAbilityId::None};
};
