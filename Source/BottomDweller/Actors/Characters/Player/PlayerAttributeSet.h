// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseAttributeSet.h"
#include "UObject/Object.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, XP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData LevelUpXP;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, LevelUpXP);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Stamina);
	
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
};
