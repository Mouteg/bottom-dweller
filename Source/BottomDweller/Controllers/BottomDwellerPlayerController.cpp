// All rights reserved by Aboba Inc.


#include "BottomDwellerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"

ABottomDwellerPlayerController::ABottomDwellerPlayerController()
{
	Sensitivity = 0.65;
	AttackSensitivityMultiplier = 0.2;
}

void ABottomDwellerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UBaseAbilitySystemComponent* ASC = Cast<ABaseCharacter>(GetCharacter())->GetAbilitySystemComponent())
	{
		AbilitySystemComponent = ASC;
	}
}

void ABottomDwellerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	TArray<uint32> BindHandles;
	BindAbilityActions(
		InputConfig,
		this,
		&ThisClass::Input_AbilityInputTagPressed,
		&ThisClass::Input_AbilityInputTagReleased,
		BindHandles
	);
}

float ABottomDwellerPlayerController::GetSensitivity()
{
	if (AbilitySystemComponent->HasMatchingGameplayTag(Tag_Event_Attack))
	{
		return AttackSensitivityMultiplier;
	}
	return Sensitivity;
}

void ABottomDwellerPlayerController::Input_AbilityInputTagPressed(FGameplayTag Tag)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->Input_AbilityInputTagPressed(Tag);
	}
}

void ABottomDwellerPlayerController::Input_AbilityInputTagReleased(FGameplayTag Tag)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->Input_AbilityInputTagReleased(Tag);
	}
}

void ABottomDwellerPlayerController::InitializeHUD()
{
	if (IsValid(HUDClass))
	{
		UUserWidget* HUD = CreateWidget(this, HUDClass);
		HUD->AddToViewport();
	}
}

void ABottomDwellerPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
}
