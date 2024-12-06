#include "MazeActor.h"

AMazeActor::AMazeActor() : MazeMeshActor(nullptr), GoalTrigger(nullptr), VolumeTrigger(nullptr), SpawnPoint(nullptr), 
PlayerController(nullptr), GameStartWidget(nullptr), InGameWidget(nullptr), GameInstance(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMazeActor::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UBallGameInstance>(UGameplayStatics::GetGameInstance(this));

	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetIgnoreLookInput(true);
	PlayerController->SetIgnoreMoveInput(true);

	if (GoalTrigger)
	{
		GoalTrigger->OnActorBeginOverlap.AddDynamic(this, &AMazeActor::OnGoalTriggerBoxBeginOverlap);
	}

	if (VolumeTrigger)
	{
		VolumeTrigger->OnActorBeginOverlap.AddDynamic(this, &AMazeActor::OnVolumeTriggerBoxBeginOverlap);
	}

	timer = 0;
	isInGame = false;
	ShowGameStartWidget();
}

void AMazeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateMaze();

	if (!isInGame)
	{
		return;
	}

	TimerCountUp(DeltaTime);
}

void AMazeActor::RotateMaze()
{
	if (MazeMeshActor && PlayerController && PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		float deltaX, deltaY;
		PlayerController->GetInputMouseDelta(deltaX, deltaY);

		FRotator currentRotation = MazeMeshActor->GetActorRotation();
		currentRotation.Roll += deltaX * RotationSpeed;
		currentRotation.Pitch -= deltaY * RotationSpeed;

		currentRotation.Roll = FMath::Clamp(currentRotation.Roll, -40, 40);
		currentRotation.Pitch = FMath::Clamp(currentRotation.Pitch, -40, 40);

		MazeMeshActor->SetActorRotation(currentRotation, ETeleportType::TeleportPhysics);
	}
}

void AMazeActor::ShowGameStartWidget()
{
	if (GameStartWidgetClass)
	{
		GameStartWidget = CreateWidget<UGameStartWidget>(PlayerController, GameStartWidgetClass);
		if (GameStartWidget)
		{
			GameStartWidget->OnStartButtonClickedDelegate.AddUniqueDynamic(this, &AMazeActor::StartGame);
			GameStartWidget->SetTitle(UGameplayStatics::GetCurrentLevelName(this, true));
			GameStartWidget->AddToViewport();
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AMazeActor::HideGameStartWidget()
{
	if (GameStartWidget && GameStartWidget->IsInViewport())
	{
		GameStartWidget->RemoveFromParent();
	}
}

void AMazeActor::ShowInGameWidget()
{
	if (InGameWidgetClass)
	{
		InGameWidget = CreateWidget<UInGameWidget>(PlayerController, InGameWidgetClass);
		if (InGameWidget)
		{
			InGameWidget->AddToViewport();
		}
	}
}

void AMazeActor::HideInGameWidget()
{
	if (InGameWidget && InGameWidget->IsInViewport())
	{
		InGameWidget->RemoveFromViewport();
	}
}

void AMazeActor::ShowEndGameWidget()
{
	if (GameEndWidgetClass)
	{
		UGameEndWidget* gameEndWidget = CreateWidget<UGameEndWidget>(PlayerController, GameEndWidgetClass);
		if (gameEndWidget)
		{
			gameEndWidget->SetTimer(timer);
			gameEndWidget->AddToViewport();
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void AMazeActor::StartGame()
{
	if (MazeMeshActor)
	{
		MazeMeshActor->SetActorRotation(FRotator::ZeroRotator);
	}

	if (BallActorClass && SpawnPoint)
	{
		FVector spawnLoc = SpawnPoint->GetActorLocation();

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		GetWorld()->SpawnActor<AActor>(BallActorClass, spawnLoc, FRotator::ZeroRotator, spawnParams);
	}

	isInGame = true;
	HideGameStartWidget();
	ShowInGameWidget();
	PlayerController->bShowMouseCursor = false;
}

void AMazeActor::OnGoalTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor->ActorHasTag(TEXT("Ball")))
	{
		HideInGameWidget();
		ShowEndGameWidget();
		isInGame = false;
	}
}

void AMazeActor::OnVolumeTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (isInGame && OtherActor && OtherActor->ActorHasTag(TEXT("Ball")))
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()));
	}
}

void AMazeActor::TimerCountUp(float deltaTime)
{
	timer += deltaTime;
	if (InGameWidget)
	{
		InGameWidget->SetTimer(timer);
	}
}

