// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/AbilitySet.h"
#include "BottomDweller/Actors/Components/SupportInterfaces/ComponentProviderSupport.h"
#include "BottomDweller/Saves/Saveable.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;

UCLASS(Abstract)
class BOTTOMDWELLER_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IComponentProviderSupport, public ISaveable
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void OnActorLoaded_Implementation() override;

	virtual UBaseAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	virtual UBaseAbilitySystemComponent* GetASCComponent_Implementation() const override
	{
		return AbilitySystemComponent;
	}

	UFUNCTION(BlueprintCallable, BlueprintSetter)
	void SetAbilitySystemComponent(UBaseAbilitySystemComponent* NewAbilitySystemComponent)
	{
		AbilitySystemComponent = NewAbilitySystemComponent;
	}
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", SaveGame)
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	UAbilitySet* AbilitySet;

private:
	void DeathTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
