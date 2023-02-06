// All rights reserved by Aboba Inc.


#include "ItemEffectCalculation.h"

#include "BottomDweller/Actors/Characters/BaseAttributeSet.h"
#include "BottomDweller/Actors/Characters/Abilities/BottomDwellerAbilitySystemGlobals.h"
#include "BottomDweller/Actors/Characters/Player/PlayerAttributeSet.h"

struct FItemStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HealthRegen);

	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxStamina);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);
	DECLARE_ATTRIBUTE_CAPTUREDEF(StaminaRegen);

	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxMana);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Mana);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ManaRegen);

	DECLARE_ATTRIBUTE_CAPTUREDEF(Dexterity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Luck);

	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponSlashingDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponBluntDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponPiercingDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(SlashingDamageResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BluntDamageResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PiercingDamageResistance);
	
	FItemStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MaxHealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Health, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, HealthRegen, Source, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, SlashingDamageResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, BluntDamageResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, PiercingDamageResistance, Source, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, MaxStamina, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Stamina, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, StaminaRegen, Source, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, MaxMana, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Mana, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, ManaRegen, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Dexterity, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Strength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Intelligence, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Luck, Source, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, WeaponSlashingDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, WeaponBluntDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, WeaponPiercingDamage, Source, false);
	}
};

static const FItemStatics& ItemStatics() {
	static FItemStatics Statics;
	return Statics;
}

UItemEffectCalculation::UItemEffectCalculation()
{
	RelevantAttributesToCapture.Add(ItemStatics().MaxHealthDef);
	RelevantAttributesToCapture.Add(ItemStatics().HealthDef);
	RelevantAttributesToCapture.Add(ItemStatics().HealthRegenDef);
	
	RelevantAttributesToCapture.Add(ItemStatics().MaxStaminaDef);
	RelevantAttributesToCapture.Add(ItemStatics().StaminaDef);
	RelevantAttributesToCapture.Add(ItemStatics().StaminaRegenDef);
	
	RelevantAttributesToCapture.Add(ItemStatics().MaxManaDef);
	RelevantAttributesToCapture.Add(ItemStatics().ManaDef);
	RelevantAttributesToCapture.Add(ItemStatics().ManaRegenDef);
	
	RelevantAttributesToCapture.Add(ItemStatics().StrengthDef);
	RelevantAttributesToCapture.Add(ItemStatics().DexterityDef);
	RelevantAttributesToCapture.Add(ItemStatics().IntelligenceDef);
	RelevantAttributesToCapture.Add(ItemStatics().LuckDef);
	
	RelevantAttributesToCapture.Add(ItemStatics().WeaponSlashingDamageDef);
	RelevantAttributesToCapture.Add(ItemStatics().WeaponBluntDamageDef);
	RelevantAttributesToCapture.Add(ItemStatics().WeaponPiercingDamageDef);

	RelevantAttributesToCapture.Add(ItemStatics().SlashingDamageResistanceDef);
	RelevantAttributesToCapture.Add(ItemStatics().BluntDamageResistanceDef);
	RelevantAttributesToCapture.Add(ItemStatics().PiercingDamageResistanceDef);
}


void UItemEffectCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	FGameplayEffectSpec* EffectSpec = ExecutionParams.GetOwningSpecForPreExecuteMod();
	const FCustomGameplayEffectContext* Context = static_cast<FCustomGameplayEffectContext*>(EffectSpec->GetContext().Get());
	const FItemStatEffect* ItemStats = Context->GetItemStatEffect();
	
	// maybe ForEachQualifiedAttributeMod
	// Does not subtract properly
	
	CurrentOutExecutionOutput = &OutExecutionOutput;

	AddOutputModifier(ItemStatics().MaxHealthProperty,  ItemStats->MaxHealth);
	AddOutputModifier(ItemStatics().HealthProperty,  ItemStats->Health);
	AddOutputModifier(ItemStatics().HealthRegenProperty,  ItemStats->HealthRegen);

	AddOutputModifier(ItemStatics().MaxStaminaProperty,  ItemStats->MaxStamina);
	AddOutputModifier(ItemStatics().StaminaProperty,  ItemStats->Stamina);
	AddOutputModifier(ItemStatics().StaminaRegenProperty,  ItemStats->StaminaRegen);

	AddOutputModifier(ItemStatics().MaxManaProperty,  ItemStats->MaxMana);
	AddOutputModifier(ItemStatics().ManaProperty,  ItemStats->Mana);
	AddOutputModifier(ItemStatics().ManaRegenProperty,  ItemStats->ManaRegen);

	AddOutputModifier(ItemStatics().StrengthProperty,  ItemStats->Strength);
	AddOutputModifier(ItemStatics().DexterityProperty,  ItemStats->Dexterity);
	AddOutputModifier(ItemStatics().IntelligenceProperty,  ItemStats->Intelligence);
	AddOutputModifier(ItemStatics().LuckProperty,  ItemStats->Luck);

	AddOutputModifier(ItemStatics().WeaponBluntDamageProperty,  ItemStats->BluntDamage);
	AddOutputModifier(ItemStatics().WeaponPiercingDamageProperty,  ItemStats->PiercingDamage);
	AddOutputModifier(ItemStatics().WeaponSlashingDamageProperty,  ItemStats->SlashingDamage);

	AddOutputModifier(ItemStatics().BluntDamageResistanceProperty,  ItemStats->BluntDamage);
	AddOutputModifier(ItemStatics().SlashingDamageResistanceProperty,  ItemStats->PiercingDamage);
	AddOutputModifier(ItemStatics().PiercingDamageResistanceProperty,  ItemStats->SlashingDamage);
}

void UItemEffectCalculation::AddOutputModifier(FProperty* Property, const float Magnitude) const
{
	if (Magnitude == 0 || !Property)
	{
		return;
	}

	CurrentOutExecutionOutput->AddOutputModifier(FGameplayModifierEvaluatedData(Property, EGameplayModOp::Additive, Magnitude));
}