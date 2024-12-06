#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BallGameInstance.generated.h"

UCLASS()
class BALLROLLINGGAME_API UBallGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();

	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> LevelNames;

private:

	int currentLevelIndex = 0;
};
