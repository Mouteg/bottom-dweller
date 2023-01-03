// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

enum class EGearSlots : uint8;

UCLASS()
class BOTTOMDWELLER_API UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	TMap<EGearSlots, FActiveGameplayEffectHandle> ActiveItemHandles;

public:
	virtual void BeginPlay() override;
	
private:
	// Handles to abilities that had their input pressed this frame.
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
	
	// Handles to abilities that had their input released this frame.
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

public:

	bool ActiveItemHandlesContain(EGearSlots Slot);
	void RemoveItemEffect(EGearSlots Slot);
	void AddItemEffect(EGearSlots Slot, UGameplayEffect* Effect);
	
	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();
	void Input_AbilityInputTagPressed(const FGameplayTag& Tag);
	void Input_AbilityInputTagReleased(const FGameplayTag& Tag);
};