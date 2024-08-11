// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/Types.h"
#include "SG_Pawn.generated.h"

class UCameraComponent;

UCLASS()
class SNAKEGAME_API ASG_Pawn : public APawn
{
	GENERATED_BODY()

public:
	ASG_Pawn();

	void UpdateLocation(const Snake::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

private:
	void OnViewportResized(FViewport* Viewport, uint32 Val);

	Snake::Dim Dim;

	int32 CellSize;

	FTransform GridOrigin;
};
