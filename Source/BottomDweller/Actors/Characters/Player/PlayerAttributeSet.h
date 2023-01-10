// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

UCLASS()
class BOTTOMDWELLER_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxMana);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, ManaRegen);
	
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Stamina);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData StaminaRegen;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, StaminaRegen);
	

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Luck);
	

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData WeaponSlashingDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WeaponSlashingDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData WeaponBluntDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WeaponBluntDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData WeaponPiercingDamage;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, WeaponPiercingDamage);
};
