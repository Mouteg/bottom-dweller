// All rights reserved by Aboba Inc.


#include "GameplayTagHelpers.h"

FGameplayTag UGameplayTagHelpers::GetComboOpeningTag()
{
	return FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.ComboOpening"));
}

FGameplayTag UGameplayTagHelpers::GetUseItemTag()
{
	return FGameplayTag::RequestGameplayTag(TEXT("Event.UseItem"));
}
