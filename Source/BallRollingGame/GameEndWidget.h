#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "GameEndWidget.generated.h"

UCLASS()
class BALLROLLINGGAME_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTimer(float time);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeNumber;
};
