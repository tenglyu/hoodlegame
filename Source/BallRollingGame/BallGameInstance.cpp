#include "BallGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBallGameInstance::Init()
{
    Super::Init();

	//LevelNames.Find(UGameplayStatics::GetCurrentLevelName(this, true), currentLevelIndex);
}

void UBallGameInstance::LoadNextLevel()
{
	currentLevelIndex = (currentLevelIndex + 1) % LevelNames.Num();

	if (LevelNames.IsValidIndex(currentLevelIndex))
	{
		UGameplayStatics::OpenLevel(this, FName(*LevelNames[currentLevelIndex]));
	}
}