// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "BottomDwellerSaveGame.h"
#include "SaveGameManager.generated.h"


UCLASS()
class BOTTOMDWELLER_API USaveGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	UPROPERTY()
	UBottomDwellerSaveGame* CurrentSaveGame;
	FString CurrentSlotName;

public:

	UFUNCTION(BlueprintCallable)
	void LoadSaveGame(FString SlotName = "");
	
	UFUNCTION()
	void SetSlotName(FString NewSlotName);
	
	UFUNCTION(BlueprintCallable)
	void WriteSaveGame(FString SlotName);

	UFUNCTION(BlueprintCallable)
	void DeleteSaveGame(FString SlotName);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
