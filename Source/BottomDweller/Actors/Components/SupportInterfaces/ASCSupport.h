// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"
#include "UObject/Interface.h"
#include "ASCSupport.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UASCSupport : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTOMDWELLER_API IASCSupport
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	UBaseAbilitySystemComponent* GetASCComponent();
};
