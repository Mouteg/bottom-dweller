// All rights reserved by Aboba Inc.


#include "BaseAttributeSet.h"

#include "BaseCharacter.h"
#include "GameplayEffectExtension.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, Attribute);
	}
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FGameplayEffectContextHandle ContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = ContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue{0.f};

	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	ABaseCharacter* TargetCharacter = {nullptr};

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetActor{nullptr};
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetCharacter = Cast<ABaseCharacter>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChange(DeltaValue, SourceTags);
		}
	}
}

void UBaseAttributeSet::AdjustAttributeForMaxChange(const FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute,
                                                    float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	//TODO maybe remove !
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = (CurrentMaxValue > 0.f)
			                       ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue
			                       : NewMaxValue;
		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}
