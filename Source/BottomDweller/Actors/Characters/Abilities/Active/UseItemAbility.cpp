// All rights reserved by Aboba Inc.


#include "UseItemAbility.h"

#include "BottomDweller/Actors/Characters/Abilities/GameplayTagHelpers.h"
#include "BottomDweller/Actors/Characters/Player/BottomDwellerCharacter.h"
#include "BottomDweller/Actors/Components/InventoryComponent/InventoryComponent.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"

UUseItemAbility::UUseItemAbility()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = UGameplayTagHelpers::GetUseItemTag();
	AbilityTriggers.Add(TriggerData);
}

void UUseItemAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UItemDataAsset* Item = CastChecked<UItemDataAsset>(TriggerEventData->OptionalObject);
	GetBottomDwellerCharacterFromActorInfo()->GetInventoryComponent()->UseItem(Item);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
