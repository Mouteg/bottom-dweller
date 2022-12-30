// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDweller/Input/AbilityInputConfig.h"
#include "BottomDwellerPlayerController.generated.h"

struct FGameplayTag;
class UBaseAbilitySystemComponent;

UCLASS()
class BOTTOMDWELLER_API ABottomDwellerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UBaseAbilitySystemComponent* GetAbilitySystem() const { return Cast<ABaseCharacter>(GetCharacter())->GetAbilitySystemComponent(); }
	
	void Input_AbilityInputTagPressed(FGameplayTag Tag);
	void Input_AbilityInputTagReleased(FGameplayTag Tag);

	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(
		const UAbilityInputConfig* InputConfig,
		UserClass* Object,
		PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc,
		TArray<uint32>& BindHandles
	);
	UPROPERTY()
	UBaseAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditDefaultsOnly)
	UAbilityInputConfig* InputConfig;

public:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};


template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void ABottomDwellerPlayerController::BindAbilityActions(
	const UAbilityInputConfig* InputConfig,
	UserClass* Object,
	PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc,
	TArray<uint32>& BindHandles
)
{
	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent, UInputComponent>(InputComponent);
	if (InputConfig)
	{
		for (FTaggedInputAction Action : InputConfig->AbilityInputActions)
		{
			if (Action.InputTag.IsValid() && Action.InputAction)
			{
				if (PressedFunc)
				{
					BindHandles.Add(
						PlayerEnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag).GetHandle());
				}
				if (ReleasedFunc)
				{
					BindHandles.Add(
						PlayerEnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle());
				}
			}
		}
	}
}
