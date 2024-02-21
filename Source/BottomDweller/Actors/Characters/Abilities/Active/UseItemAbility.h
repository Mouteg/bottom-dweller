// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseGameplayAbility.h"
#include "UseItemAbility.generated.h"

struct FItemStatEffect;
class UItemDataAsset;
/**
 * 
 */
UCLASS()
class BOTTOMDWELLER_API UUseItemAbility : public UBaseGameplayAbility {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantEffect;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effects")
	TSubclassOf<UGameplayEffect> DurationEffect;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effects")
	TSubclassOf<UGameplayEffect> InfiniteEffect;

private:
	UUseItemAbility();
	FGameplayEffectSpec* CurrentEffectSpec;

	void MakeEffectSpecAndUseItem(UItemDataAsset* Item);
	void AddSetByCallers(const FItemStatEffect* ItemStatEffect);
	void AddSetByCaller(FGameplayTag Tag, float Magnitude);


	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
};
