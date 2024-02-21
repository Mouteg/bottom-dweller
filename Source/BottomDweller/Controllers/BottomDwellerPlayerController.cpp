// All rights reserved by Aboba Inc.


#include "BottomDwellerPlayerController.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BottomDweller/UI/BottomDwellerHUD.h"

ABottomDwellerPlayerController::ABottomDwellerPlayerController() {
	Sensitivity = 0.65;
	AttackSensitivityMultiplier = 0.2;
	MaxBodyPitch = 90;
	MinBodyPitch = -90;
	BodyPitch = 0;
}

void ABottomDwellerPlayerController::BeginPlay() {
	Super::BeginPlay();

	if (UBaseAbilitySystemComponent* ASC = IASCProviderSupport::Execute_GetASCComponent(GetPawn())) {
		AbilitySystemComponent = ASC;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(GameContext, 0);
	}
}

void ABottomDwellerPlayerController::SetupInputComponent() {
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

float ABottomDwellerPlayerController::GetSensitivity() {
	if (AbilitySystemComponent->HasMatchingGameplayTag(Tag_Event_Attack)) {
		return AttackSensitivityMultiplier;
	}
	return Sensitivity;
}

void ABottomDwellerPlayerController::SwitchGameMenuVisibility() {
	if (const ABottomDwellerHUD* HUD = Cast<ABottomDwellerHUD>(GetHUD())) {
		HUD->IsMenuVisible() ? SetGameMenuHidden() : SetGameMenuVisible();
	}
}

void ABottomDwellerPlayerController::SetGameMenuVisible() {
	if (ABottomDwellerHUD* HUD = Cast<ABottomDwellerHUD>(GetHUD())) {
		HUD->SetGameMenuVisible();
	}
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

void ABottomDwellerPlayerController::SetGameMenuHidden() {
	if (ABottomDwellerHUD* HUD = Cast<ABottomDwellerHUD>(GetHUD())) {
		HUD->SetGameMenuHidden();
	}
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ABottomDwellerPlayerController::AddCameraInput(float X, float Y) {
	X *= GetSensitivity();
	Y *= GetSensitivity();

	AddYawInput(X);
	AddPitchInput(Y);
	BodyPitch = FMath::Clamp(Y * -1 + BodyPitch, MinBodyPitch, MaxBodyPitch);
}

void ABottomDwellerPlayerController::Input_AbilityInputTagPressed(FGameplayTag Tag) {
	if (AbilitySystemComponent) {
		AbilitySystemComponent->Input_AbilityInputTagPressed(Tag);
	}
}

void ABottomDwellerPlayerController::Input_AbilityInputTagReleased(FGameplayTag Tag) {
	if (AbilitySystemComponent) {
		AbilitySystemComponent->Input_AbilityInputTagReleased(Tag);
	}
}

void ABottomDwellerPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused) {
	Super::PostProcessInput(DeltaTime, bGamePaused);
	if (AbilitySystemComponent) {
		AbilitySystemComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
}
