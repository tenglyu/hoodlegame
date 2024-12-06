#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameStartWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartButtonClickedSignature);

UCLASS()
class BALLROLLINGGAME_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnStartButtonClicked();

	UPROPERTY(BlueprintAssignable)
	FOnStartButtonClickedSignature OnStartButtonClickedDelegate;

	UFUNCTION(BlueprintCallable)
	void SetTitle(FString title);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescriptionText;
};
