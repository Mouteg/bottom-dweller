// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"


UENUM(BlueprintType)
enum class EInputAbilityId : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
	Fireball UMETA(DisplayName = "Fireball")
};

UCLASS()
class BOTTOMDWELLER_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseGameplayAbility();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	EInputAbilityId AbilityInputId{EInputAbilityId::None};
};
