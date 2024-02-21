// All rights reserved by Aboba Inc.


#include "BaseCharacter.h"

#include "Abilities/TagDeclarations.h"


ABaseCharacter::ABaseCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("Ability System Component"));
}

void ABaseCharacter::BeginPlay() {
	Super::BeginPlay();
	if (AbilitySet && AbilitySystemComponent) {
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, this);
		AbilitySystemComponent->RegisterGameplayTagEvent(Tag_Gameplay_Dead, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::DeathTagChanged);
	}
}

void ABaseCharacter::DeathTagChanged(const FGameplayTag CallbackTag, int32 NewCount) {
	if (NewCount > 0) {
		Destroy();
	}
}

void ABaseCharacter::OnActorLoaded_Implementation() {
}
