// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BottomDwellerGameMode.generated.h"

UCLASS(minimalapi)
class ABottomDwellerGameMode : public AGameModeBase {
	GENERATED_BODY()

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	ABottomDwellerGameMode();

private:
	void LoadPrimaryAssets();
};
