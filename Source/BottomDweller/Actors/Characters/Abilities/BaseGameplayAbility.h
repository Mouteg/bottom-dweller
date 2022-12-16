// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

class ABottomDwellerPlayerController;
class ABaseCharacter;

UCLASS()
class BOTTOMDWELLER_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	ABottomDwellerPlayerController* GetPlayerControllerFromActorInfo() const;
	ABaseCharacter* GetCharacterFromActorInfo() const;
};
