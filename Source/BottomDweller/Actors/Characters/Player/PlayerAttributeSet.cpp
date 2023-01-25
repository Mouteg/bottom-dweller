#include "PlayerAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
		if (GetStamina() == 0)
		{
			FGameplayTagContainer TagsToCancel;
			TagsToCancel.AddTag(Tag_Ability_Sprint);
			GetOwningAbilitySystemComponent()->CancelAbilities(&TagsToCancel);
		}
	}
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}
