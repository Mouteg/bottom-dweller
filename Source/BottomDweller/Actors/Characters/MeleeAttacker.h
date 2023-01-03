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
public:
	virtual void BeginAttack() = 0;
	virtual void EndAttack() = 0;
	virtual void EnableWeaponCollision() = 0;
	virtual void DisableWeaponCollision() = 0;
};
