// All rights reserved by Aboba Inc.


#include "UseItemAbility.h"

#include "BottomDweller/Actors/Characters/Abilities/BottomDwellerAbilitySystemGlobals.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"

UUseItemAbility::UUseItemAbility()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = UBottomDwellerAbilitySystemGlobals::GSGet().UseItemTag;
	AbilityTriggers.Add(TriggerData);
}

void UUseItemAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
									  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UItemDataAsset* Item = CastChecked<UItemDataAsset>(TriggerEventData->OptionalObject);

	if (!Item)
	{
		return;
	}

	MakeEffectSpec(Item);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UUseItemAbility::MakeEffectSpec(UItemDataAsset* Item)
{
	FGameplayEffectSpecHandle Spec;
	switch (Item->ItemType)
	{
	case EItemType::Gear:
		{
			Spec = MakeOutgoingGameplayEffectSpec(InfiniteEffect);
			break;
		}
	case EItemType::Consumable:
		{
			Spec = MakeOutgoingGameplayEffectSpec(InstantEffect);
			break;
		}
	default: return;
	}
	CurrentEffectSpec = Spec.Data.Get();
	AddSetByCallers(&Item->ItemStatEffect);
	GetBottomDwellerCharacterFromActorInfo()->GetInventoryComponent()->UseItem(Item, *CurrentEffectSpec);
}

void UUseItemAbility::AddSetByCallers(const FItemStatEffect* ItemStatEffect)
{
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().MaxHealthTag, ItemStatEffect->MaxHealth);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().HealthTag, ItemStatEffect->Health);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().HealthRegenTag, ItemStatEffect->HealthRegen);
	
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().MaxManaTag, ItemStatEffect->MaxMana);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().ManaTag, ItemStatEffect->Mana);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().ManaRegenTag, ItemStatEffect->ManaRegen);
	
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().MaxStaminaTag, ItemStatEffect->MaxStamina);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().StaminaTag, ItemStatEffect->Stamina);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().StaminaRegenTag, ItemStatEffect->StaminaRegen);
	
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().StrengthTag, ItemStatEffect->Strength);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().DexterityTag, ItemStatEffect->Dexterity);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().IntelligenceTag, ItemStatEffect->Intelligence);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().LuckTag, ItemStatEffect->Luck);
	
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().SlashingDamageTag, ItemStatEffect->SlashingDamage);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().BluntDamageTag, ItemStatEffect->BluntDamage);
	AddSetByCaller(UBottomDwellerAbilitySystemGlobals::GSGet().PiercingDamageTag, ItemStatEffect->PiercingDamage);
}


void UUseItemAbility::AddSetByCaller(FGameplayTag Tag, float Magnitude)
{
	CurrentEffectSpec->SetByCallerTagMagnitudes.Add(Tag, Magnitude);
}
