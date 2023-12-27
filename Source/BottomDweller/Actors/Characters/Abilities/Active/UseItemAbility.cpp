// All rights reserved by Aboba Inc.


#include "UseItemAbility.h"

#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/Actors/Components/InventoryComponent.h"
#include "BottomDweller/Controllers/PlayerInventoryController.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "BottomDweller/Util/UUtils.h"

class UPlayerInventoryController;

UUseItemAbility::UUseItemAbility()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = Tag_Event_UseItem;
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

	MakeEffectSpecAndUseItem(Item);
	// Not sure why i wrote this, if something breaks - try this
	// else
	// {
	// 	UUtils::GetInventorySubsystem(GetWorld())->AddItem(Item);
	// }
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UUseItemAbility::MakeEffectSpecAndUseItem(UItemDataAsset* Item)
{
	FGameplayEffectSpecHandle Spec;
	switch (Item->ItemType)
	{
	case EItemType::Weapon:
		{
			Spec = MakeOutgoingGameplayEffectSpec(InfiniteEffect);
			// Spec.Data->
			break;
		}
	case EItemType::Armor:
		{
			Spec = MakeOutgoingGameplayEffectSpec(InfiniteEffect);
			// Spec.Data->
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
	UUtils::GetInventorySubsystem(GetWorld())->UseItem(Item, *CurrentEffectSpec);
}

void UUseItemAbility::AddSetByCallers(const FItemStatEffect* ItemStatEffect)
{
	AddSetByCaller(Tag_Attribute_MaxHealth, ItemStatEffect->MaxHealth);
	AddSetByCaller(Tag_Attribute_Health, ItemStatEffect->Health);
	AddSetByCaller(Tag_Attribute_HealthRegen, ItemStatEffect->HealthRegen);

	AddSetByCaller(Tag_Attribute_MaxMana, ItemStatEffect->MaxMana);
	AddSetByCaller(Tag_Attribute_Mana, ItemStatEffect->Mana);
	AddSetByCaller(Tag_Attribute_ManaRegen, ItemStatEffect->ManaRegen);

	AddSetByCaller(Tag_Attribute_MaxStamina, ItemStatEffect->MaxStamina);
	AddSetByCaller(Tag_Attribute_Stamina, ItemStatEffect->Stamina);
	AddSetByCaller(Tag_Attribute_StaminaRegen, ItemStatEffect->StaminaRegen);

	AddSetByCaller(Tag_Attribute_Strength, ItemStatEffect->Strength);
	AddSetByCaller(Tag_Attribute_Dexterity, ItemStatEffect->Dexterity);
	AddSetByCaller(Tag_Attribute_Intelligence, ItemStatEffect->Intelligence);
	AddSetByCaller(Tag_Attribute_Luck, ItemStatEffect->Luck);

	AddSetByCaller(Tag_Attribute_SlashingDamage, ItemStatEffect->SlashingDamage);
	AddSetByCaller(Tag_Attribute_BluntDamage, ItemStatEffect->BluntDamage);
	AddSetByCaller(Tag_Attribute_PiercingDamage, ItemStatEffect->PiercingDamage);

	AddSetByCaller(Tag_Attribute_SlashingDamageResistance, ItemStatEffect->SlashingDamageResistance);
	AddSetByCaller(Tag_Attribute_BluntDamageResistance, ItemStatEffect->BluntDamageResistance);
	AddSetByCaller(Tag_Attribute_PiercingDamageResistance, ItemStatEffect->PiercingDamageResistance);
}


void UUseItemAbility::AddSetByCaller(FGameplayTag Tag, float Magnitude)
{
	CurrentEffectSpec->SetByCallerTagMagnitudes.Add(Tag, Magnitude);
}
