// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilityInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FTaggedInputAction {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

UCLASS(BlueprintType, Const)
class BOTTOMDWELLER_API UAbilityInputConfig : public UDataAsset {
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintCallable)
	// const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;
	//
	// UFUNCTION(BlueprintCallable)
	// const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTaggedInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FTaggedInputAction> AbilityInputActions;
};
