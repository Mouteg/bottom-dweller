// All rights reserved by Aboba Inc.


#include "DamageCalculation.h"
#include "BottomDweller/Actors/Characters/BaseAttributeSet.h"

UDamageCalculation::UDamageCalculation()
{
	BluntResistanceDef.AttributeToCapture = UBaseAttributeSet::GetBluntDamageResistanceAttribute();
	BluntResistanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	SlashingResistanceDef.AttributeToCapture = UBaseAttributeSet::GetSlashingDamageResistanceAttribute();
	SlashingResistanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	PiercingResistanceDef.AttributeToCapture = UBaseAttributeSet::GetPiercingDamageResistanceAttribute();
	PiercingResistanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	PiercingDamageDef.AttributeToCapture = UBaseAttributeSet::GetPiercingDamageAttribute();
	BluntDamageDef.AttributeToCapture = UBaseAttributeSet::GetBluntDamageAttribute();
	SlashingDamageDef.AttributeToCapture = UBaseAttributeSet::GetSlashingDamageAttribute();

	RelevantAttributesToCapture.Add(BluntResistanceDef);
	RelevantAttributesToCapture.Add(SlashingResistanceDef);
	RelevantAttributesToCapture.Add(PiercingResistanceDef);

	RelevantAttributesToCapture.Add(PiercingDamageDef);
	RelevantAttributesToCapture.Add(BluntDamageDef);
	RelevantAttributesToCapture.Add(SlashingDamageDef);
}

float UDamageCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BluntResistance = 0;
	GetCapturedAttributeMagnitude(BluntResistanceDef, Spec, EvaluationParameters, BluntResistance);
	float SlashingResistance = 0;
	GetCapturedAttributeMagnitude(SlashingResistanceDef, Spec, EvaluationParameters, SlashingResistance);
	float PiercingResistance = 0;
	GetCapturedAttributeMagnitude(PiercingResistanceDef, Spec, EvaluationParameters, PiercingResistance);

	float PiercingDamage = 0;
	GetCapturedAttributeMagnitude(PiercingDamageDef, Spec, EvaluationParameters, PiercingDamage);
	float BluntDamage = 0;
	GetCapturedAttributeMagnitude(BluntDamageDef, Spec, EvaluationParameters, BluntDamage);
	float SlashingDamage = 0;
	GetCapturedAttributeMagnitude(SlashingDamageDef, Spec, EvaluationParameters, SlashingDamage);

	const float Damage = FMath::Max(BluntDamage - BluntResistance, 0)
		+ FMath::Max(SlashingDamage - SlashingResistance, 0)
		+ FMath::Max(PiercingDamage - PiercingResistance, 0);

	UE_LOG(LogTemp, Warning, TEXT("Damage dealt: %s"), *FString::FromInt(Damage))
	return Damage;
}
