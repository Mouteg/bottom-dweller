// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/AbilitySet.h"
#include "BottomDweller/Saves/Saveable.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;

UCLASS(Abstract)
class BOTTOMDWELLER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ISaveable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities", SaveGame)
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	UAbilitySet* AbilitySet;
public:
	virtual void OnActorLoaded_Implementation() override;

	virtual UBaseAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	};
};
