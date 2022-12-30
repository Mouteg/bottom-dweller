// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "ItemDetailsEntry.h"
#include "Blueprint/UserWidget.h"
#include "ItemDetailsPanel.generated.h"

class UItemDataAsset;

UCLASS()
class BOTTOMDWELLER_API UItemDetailsPanel : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void LoadItemProperties(UItemDataAsset* Item);

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* PropertiesContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DisplayName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Description;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Thumbnail;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UItemDetailsEntry> DetailsEntryWidget;

	UFUNCTION()
	void LoadDetails(UItemDataAsset* Item);

	virtual bool Initialize() override;
};
