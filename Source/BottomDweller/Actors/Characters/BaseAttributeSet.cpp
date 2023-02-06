// All rights reserved by Aboba Inc.


#include "BaseAttributeSet.h"

#include "BaseCharacter.h"
#include "GameplayEffectExtension.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

// float UBaseAttributeSet::GetBluntDamageValue(const ABaseCharacter* Character)
// {
// 	if (IsValid(Character))
// 	{
// 		bool Found;
// 		return Character->GetAbilitySystemComponent()->GetGameplayAttributeValue(GetBluntDamageAttribute(), Found);
// 	}
// 	return 0;
// }
//
// float UBaseAttributeSet::GetSlashingDamageValue(const ABaseCharacter* Character)
// {
// 	if (IsValid(Character))
// 	{
// 		bool Found;
// 		return Character->GetAbilitySystemComponent()->GetGameplayAttributeValue(GetSlashingDamageAttribute(), Found);
// 	}
// 	return 0;
// }
//
// float UBaseAttributeSet::GetPiercingDamageValue(const ABaseCharacter* Character)
// {
// 	if (IsValid(Character))
// 	{
// 		bool Found;
// 		return Character->GetAbilitySystemComponent()->GetGameplayAttributeValue(GetPiercingDamageAttribute(), Found);
// 	}
// 	return 0;
// }
