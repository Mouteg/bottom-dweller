// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

class ABottomDwellerCharacter;
class ABottomDwellerPlayerController;
class ABaseCharacter;

UENUM(BlueprintType)
enum class EAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	OnSpawn,
};

UCLASS()
class BOTTOMDWELLER_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Activation")
	EAbilityActivationPolicy ActivationPolicy;

public:
	UPROPERTY(EditDefaultsOnly, Category=Costs)
	float Cost;
	
	EAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	UAbilitySystemComponent* GetAbilitySystemComponentFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo = nullptr) const;
	ABottomDwellerPlayerController* GetPlayerControllerFromActorInfo() const;
	ABaseCharacter* GetCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo = nullptr) const;
	ABottomDwellerCharacter* GetBottomDwellerCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo = nullptr) const;
	ABaseCharacter* GetBaseCharacterFromActorInfo(const FGameplayAbilityActorInfo* ActorInfo = nullptr) const;
};
