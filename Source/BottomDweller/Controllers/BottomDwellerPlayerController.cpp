// All rights reserved by Aboba Inc.


#include "BottomDwellerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"

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
	if (UUserWidget* HUD = CreateWidget(this, HUDClass))
	{
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
