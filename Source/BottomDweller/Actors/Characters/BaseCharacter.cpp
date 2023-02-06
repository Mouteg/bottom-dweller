// All rights reserved by Aboba Inc.


#include "BaseCharacter.h"

#include "BottomDweller/Controllers/BottomDwellerPlayerController.h"


ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("Ability System Component"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySet && AbilitySystemComponent)
	{
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, this);
	}
}

void ABaseCharacter::OnActorLoaded_Implementation()
{
	
}
