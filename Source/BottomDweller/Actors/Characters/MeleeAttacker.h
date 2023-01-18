// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeleeAttacker.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMeleeAttacker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOTTOMDWELLER_API IMeleeAttacker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	// Implement functions below statically
public:
	UFUNCTION(BlueprintNativeEvent)
	void BeginAttack();
	UFUNCTION(BlueprintNativeEvent)
	void EndAttack();
	UFUNCTION(BlueprintNativeEvent)
	void EnableWeaponCollision();
	UFUNCTION(BlueprintNativeEvent)
	void DisableWeaponCollision();
};
