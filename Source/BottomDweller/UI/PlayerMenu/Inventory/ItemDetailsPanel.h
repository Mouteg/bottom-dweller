// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "TextEntry.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "ItemDetailsPanel.generated.h"

UCLASS()
class BOTTOMDWELLER_API UItemDetailsPanel : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void LoadItemProperties(UItemDataAsset* Item);

	UFUNCTION()
	void CreateDetailsEntries(FItemStatEffect StatEffect);

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
	TSubclassOf<UTextEntry> DetailsEntryWidget;

	UFUNCTION()
	void LoadDetails(UItemDataAsset* Item);

	virtual bool Initialize() override;
};
