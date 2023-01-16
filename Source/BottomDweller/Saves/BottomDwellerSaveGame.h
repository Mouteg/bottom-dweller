// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BottomDwellerSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()

	/* Identifier for which Actor this belongs to */
	UPROPERTY()
	FName ActorName;

	/* For movable Actors, keep location,rotation,scale. */
	UPROPERTY()
	FTransform Transform;

	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY()
	TArray<uint8> ByteData;
};

USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	bool bResumeAtTransform;
};

UCLASS()
class BOTTOMDWELLER_API UBottomDwellerSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FPlayerSaveData SavedPlayer;

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;
};
