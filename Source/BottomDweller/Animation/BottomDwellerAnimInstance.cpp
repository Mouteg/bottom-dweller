// All rights reserved by Aboba Inc.


#include "BottomDwellerAnimInstance.h"
#include "AbilitySystemGlobals.h"

void UBottomDwellerAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* ASC) {
	check(ASC);
	GameplayTagPropertyMap.Initialize(this, ASC);
}

void UBottomDwellerAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	if (AActor* OwningActor = GetOwningActor()) {
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwningActor)) {
			InitializeWithAbilitySystem(ASC);
		}
	}
}
