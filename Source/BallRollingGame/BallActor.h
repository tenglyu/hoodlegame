#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class BALLROLLINGGAME_API ABallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
