// All rights reserved by Aboba Inc.


#include "BottomDwellerPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/Actors/Characters/Abilities/TagDeclarations.h"
#include "BottomDweller/Actors/Characters/Abilities/BaseAbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "BottomDweller/UI/PlayerMenu/Inventory/InventoryPanel.h"

ABottomDwellerPlayerController::ABottomDwellerPlayerController()
{
	Sensitivity = 0.65;
	AttackSensitivityMultiplier = 0.2;
	MaxBodyPitch = 90;
	MinBodyPitch = -90;
	BodyPitch = 0;
}

void ABottomDwellerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UBaseAbilitySystemComponent* ASC = IASCProviderSupport::Execute_GetASCComponent(GetPawn()))
	{
		AbilitySystemComponent = ASC;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(GameContext, 0);
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

void ABottomDwellerPlayerController::SwitchGameMenuVisibility()
{
	PlayerMenuWidgetSwitcher->IsVisible() ? SetGameMenuHidden() : SetGameMenuVisible();
}

void ABottomDwellerPlayerController::SetGameMenuVisible()
{
	PlayerMenuWidgetSwitcher->SetVisibility(ESlateVisibility::Visible);
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

void ABottomDwellerPlayerController::SetGameMenuHidden()
{
	PlayerMenuWidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ABottomDwellerPlayerController::AddCameraInput(float X, float Y)
{
	X *= GetSensitivity();
	Y *= GetSensitivity();

	AddYawInput(X);
	AddPitchInput(Y);
	BodyPitch = FMath::Clamp(Y * -1 + BodyPitch, MinBodyPitch, MaxBodyPitch);
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

void ABottomDwellerPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
}


void ABottomDwellerPlayerController::InitializeHUD()
{
	if (IsValid(HUDClass))
	{
		UUserWidget* HUD = CreateWidget(this, HUDClass);
		HUD->AddToViewport();
	}


	if (IsValid(PlayerMenuWidgetSwitcherClass))
	{
		PlayerMenuWidgetSwitcher = CreateWidget(this, PlayerMenuWidgetSwitcherClass);
		PlayerMenuWidgetSwitcher->AddToViewport();
		PlayerMenuWidgetSwitcher->SetVisibility(ESlateVisibility::Hidden);

		// TArray<UWidget*> a;
		// PlayerMenuWidgetSwitcher->WidgetTree->FindWidget("InventoryUI");
		// for (const auto Widget : a)
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *Widget->GetName());
		// }
		// if (UWidget* ContainerInventoryPanelWidget = PlayerMenuWidgetSwitcher->WidgetTree->FindWidget("ContainerInventoryPanel"))
		// {
		// 	ContainerInventoryPanel = Cast<UInventoryPanel>(ContainerInventoryPanelWidget);
		// }
	}
}

void ABottomDwellerPlayerController::OpenContainer(TObjectPtr<UInventoryComponent> InventoryComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Opened"));

	if (IsValid(ContainerInventoryPanel))
	{
		ContainerInventoryPanel->SetInventory(InventoryComponent);
	}

	// Open container menu
	// Set slots
	// Set container widget visible
}
