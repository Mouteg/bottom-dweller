// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BaseAttributeSet.generated.h"

#define GAMEPLAYATTRIBUTE_STATIC_VALUE_GETTER(PropertyName) \
	FORCEINLINE static float Get##PropertyName##Value(ABaseCharacter* Character) \
	{ \
		ensure(Character); \
		UBaseAbilitySystemComponent* AbilityComp = IASCProviderSupport::Execute_GetASCComponent(Character); \
		if (ensure(AbilityComp)) \
		{ \
			bool Found; \
			float Value = AbilityComp->GetGameplayAttributeValue(Get##PropertyName##Attribute(), Found); \
			return Found ? Value : 0; \
		} \
		return 0; \
	}

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_STATIC_VALUE_GETTER(PropertyName)
/*
 * When adding new attributes:
 * 1) FItemStatEffect
 * 2) UUseItemAbility::AddSetByCallers
 * 3) UItemEffectCalculation
 * 4) Edit Simple stats widget
 * 5) Modify 3 GE in editor
 * 6) Add new tags
 */

UCLASS()
class BOTTOMDWELLER_API UBaseAttributeSet : public UAttributeSet {
	GENERATED_BODY()

public:
	UBaseAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
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

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData SlashingDamageResistance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, SlashingDamageResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData BluntDamageResistance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, BluntDamageResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData PiercingDamageResistance;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, PiercingDamageResistance);

	
};
