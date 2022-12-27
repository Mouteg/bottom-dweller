// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BottomDweller/Actors/Characters/BaseCharacter.h"
#include "BottomDwellerCharacter.generated.h"

class ABottomDwellerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, ABottomDwellerCharacter*, Interactor);

UCLASS(config=Game)
class ABottomDwellerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ABottomDwellerCharacter();

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintPure, BlueprintCallable, BlueprintGetter)
	UInventoryComponent* GetInventoryComponent() const
	{
		return InventoryComponent;
	}

	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;

protected:
	/** Called for movement input */
	UFUNCTION(BlueprintCallable)
	void Move(float ForwardValue, float RightValue);

	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
