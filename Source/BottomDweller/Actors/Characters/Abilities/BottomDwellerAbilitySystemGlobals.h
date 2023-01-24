// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "BottomDwellerAbilitySystemGlobals.generated.h"

USTRUCT()
struct FCustomGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	const FItemStatEffect* GetItemStatEffect() const
	{
			return &ItemStatEffect;
	}

	void SetItemStatEffect(const FItemStatEffect Effect)
	{
		ItemStatEffect = Effect;
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual FGameplayEffectContext* Duplicate() const override
	{
		FCustomGameplayEffectContext* NewContext = new FCustomGameplayEffectContext();
		*NewContext = *this;
		NewContext->AddActors(Actors);
		NewContext->ItemStatEffect = ItemStatEffect;
		return NewContext;
	}

	FItemStatEffect ItemStatEffect = {};
};


template <>
struct TStructOpsTypeTraits<FCustomGameplayEffectContext> : TStructOpsTypeTraitsBase2<FCustomGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

UCLASS()
class BOTTOMDWELLER_API UBottomDwellerAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	UBottomDwellerAbilitySystemGlobals();

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
