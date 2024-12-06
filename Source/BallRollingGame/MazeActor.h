#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "BallActor.h"
#include "GameStartWidget.h"
#include "InGameWidget.h"
#include "GameEndWidget.h"
#include "BallGameInstance.h"
#include "MazeActor.generated.h"

UCLASS()
class BALLROLLINGGAME_API AMazeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMazeActor();

	UFUNCTION(BlueprintCallable)
	void RotateMaze();

	UFUNCTION(BlueprintCallable)
	void ShowGameStartWidget();

	UFUNCTION(BlueprintCallable)
	void HideGameStartWidget();

	UFUNCTION(BlueprintCallable)
	void ShowInGameWidget();

	UFUNCTION(BlueprintCallable)
	void HideInGameWidget();

	UFUNCTION(BlueprintCallable)
	void ShowEndGameWidget();

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void OnGoalTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnVolumeTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	AActor* MazeMeshActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	ATriggerBox* GoalTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	ATriggerBox* VolumeTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	AActor* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maze")
	TSubclassOf<ABallActor> BallActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UGameStartWidget> GameStartWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInGameWidget> InGameWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UGameEndWidget> GameEndWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Maze")
	float RotationSpeed = 0.5f;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UBallGameInstance* GameInstance;
	APlayerController* PlayerController;
	UGameStartWidget* GameStartWidget;
	UInGameWidget* InGameWidget;

private:
	void TimerCountUp(float deltaTime);

	float timer = 0;
	bool isInGame = false;

};
