// All rights reserved by Aboba Inc.

#pragma once

#include "CoreMinimal.h"
#include "TextEntry.h"
#include "Blueprint/UserWidget.h"
#include "BottomDweller/DataAssets/Items/ItemDataAsset.h"
#include "ItemDetailsPanel.generated.h"

class UImage;
class UVerticalBox;

UCLASS()
class BOTTOMDWELLER_API UItemDetailsPanel : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> PropertiesContainer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> DisplayName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> Description;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Thumbnail;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTextEntry> DetailsEntryWidget;

	UFUNCTION()
	void LoadDetails(UItemDataAsset* Item);

	virtual bool Initialize() override;

private:
	UFUNCTION()
	void LoadItemProperties(UItemDataAsset* Item);

	UFUNCTION()
	void CreateDetailsEntries(FItemStatEffect StatEffect);
};
