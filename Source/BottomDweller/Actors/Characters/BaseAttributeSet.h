// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class BOTTOMDWELLER_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HealthRegen);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData SlashingDamage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, SlashingDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData BluntDamage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, BluntDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData PiercingDamage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, PiercingDamage);
};
