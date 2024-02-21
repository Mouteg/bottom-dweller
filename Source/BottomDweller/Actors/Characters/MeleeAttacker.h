// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeleeAttacker.generated.h"

UINTERFACE()
class UMeleeAttacker : public UInterface {
	GENERATED_BODY()
};

class BOTTOMDWELLER_API IMeleeAttacker {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void BeginAttack();
	UFUNCTION(BlueprintNativeEvent)
	void EndAttack();
	UFUNCTION(BlueprintNativeEvent)
	void EnableWeaponTracing();
	UFUNCTION(BlueprintNativeEvent)
	void DisableWeaponTracing();
};
