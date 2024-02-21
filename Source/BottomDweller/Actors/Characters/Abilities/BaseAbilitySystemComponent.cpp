// All rights reserved by Aboba Inc.
#include "BaseAbilitySystemComponent.h"
#include "BaseGameplayAbility.h"
#include "TagDeclarations.h"


void UBaseAbilitySystemComponent::BeginPlay() {
	Super::BeginPlay();
	ClearAbilityInput();
}

void UBaseAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused) {
	if (HasMatchingGameplayTag(Tag_Gameplay_AbilityInputBlocked)) {
		ClearAbilityInput();
		return;
	}

	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles) {
		if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle)) {
			if (AbilitySpec->Ability && !AbilitySpec->IsActive()) {
				const UBaseGameplayAbility* AbilityCDO = CastChecked<UBaseGameplayAbility>(AbilitySpec->Ability);

				if (AbilityCDO->GetActivationPolicy() == EAbilityActivationPolicy::WhileInputActive) {
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles) {
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle)) {
			if (AbilitySpec->Ability) {
				AbilitySpec->InputPressed = true;
				if (AbilitySpec->IsActive()) {
					// Ability is active so pass along the input event.
					AbilitySpecInputPressed(*AbilitySpec);
				} else {
					const UBaseGameplayAbility* AbilityCDO = CastChecked<UBaseGameplayAbility>(AbilitySpec->Ability);

					if (AbilityCDO->GetActivationPolicy() == EAbilityActivationPolicy::OnInputTriggered) {
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}

	//
	// Try to activate all the abilities that are from presses and holds.
	// We do it all at once so that held inputs don't activate the ability
	// and then also send a input event to the ability because of the press.
	//
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate) {
		TryActivateAbility(AbilitySpecHandle);
	}

	//
	// Process all abilities that had their input released this frame.
	//
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles) {
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle)) {
			if (AbilitySpec->Ability) {
				AbilitySpec->InputPressed = false;

				if (AbilitySpec->IsActive()) {
					// Ability is active so pass along the input event.
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UBaseAbilitySystemComponent::ClearAbilityInput() {
	InputPressedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UBaseAbilitySystemComponent::Input_AbilityInputTagPressed(const FGameplayTag& Tag) {
	if (Tag.IsValid()) {
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items) {
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(Tag)) {
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UBaseAbilitySystemComponent::Input_AbilityInputTagReleased(const FGameplayTag& Tag) {
	if (Tag.IsValid()) {
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items) {
			if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))) {
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}
