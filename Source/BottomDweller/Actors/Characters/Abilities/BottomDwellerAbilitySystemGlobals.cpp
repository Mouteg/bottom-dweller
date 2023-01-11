// All rights reserved by Aboba Inc.


#include "BottomDwellerAbilitySystemGlobals.h"

UBottomDwellerAbilitySystemGlobals::UBottomDwellerAbilitySystemGlobals()
{
}

FGameplayEffectContext* UBottomDwellerAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FCustomGameplayEffectContext();
}

void UBottomDwellerAbilitySystemGlobals::InitGlobalTags()
{
	Super::InitGlobalTags();
	ComboOpeningTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.ComboOpening"));
	UseItemTag = FGameplayTag::RequestGameplayTag(TEXT("Event.UseItem"));
	SprintAbility = FGameplayTag::RequestGameplayTag(TEXT("Ability.Sprint"));

	MaxHealthTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.MaxHealth"));
	HealthTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Health"));
	HealthRegenTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.HealthRegen"));

	MaxStaminaTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.MaxStamina"));
	StaminaTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Stamina"));
	StaminaRegenTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.StaminaRegen"));

	MaxManaTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.MaxMana"));
	ManaTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Mana"));
	ManaRegenTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.ManaRegen"));

	StrengthTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Strength"));
	DexterityTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Dexterity"));
	IntelligenceTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Intelligence"));
	LuckTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.Luck"));

	SlashingDamageTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.SlashingDamage"));
	BluntDamageTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.BluntDamage"));
	PiercingDamageTag = FGameplayTag::RequestGameplayTag(TEXT("Attribute.PiercingDamage"));
}
