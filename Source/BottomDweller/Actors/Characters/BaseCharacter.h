// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseAttributeSet.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseGameplayAbility.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class BOTTOMDWELLER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth();

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;

	friend UBaseAttributeSet;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(const float Damage, const FHitResult& HitResult, const struct FGameplayTagContainer& DamageTags,
	               ABaseCharacter* CharacterInstigator, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChange(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual void HandleDamage(const float Damage, const FHitResult& HitResult, const struct FGameplayTagContainer& DamageTags,
	                          ABaseCharacter* CharacterInstigator, AActor* DamageCauser);

	virtual void HandleHealthChange(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void AddInitialGameplayAbilities();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UBaseGameplayAbility>> GameplayAbilities;

	UPROPERTY()
	uint8 bAbilitiesInitialized:1;
};
