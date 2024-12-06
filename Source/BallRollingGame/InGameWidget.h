#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InGameWidget.generated.h"

UCLASS()
class BALLROLLINGGAME_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTimer(float time);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeNumber;
};
