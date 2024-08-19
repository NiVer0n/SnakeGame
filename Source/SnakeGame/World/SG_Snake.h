// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Snake.h"
#include "SG_Snake.generated.h"

class ASG_SnakeLink;
struct FSnakeColors;

UCLASS()
class SNAKEGAME_API ASG_Snake : public AActor
{
	GENERATED_BODY()

public:
	ASG_Snake();

	void SetModel(const TSharedPtr<SnakeGame::Snake>& InSnake, uint32 InCellSize, const SnakeGame::Dim& InDims);

	void UpdateColors(const FSnakeColors& Colors);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_SnakeLink> SnakeHeadClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ASG_SnakeLink> SnakeLinkClass;

public:
	virtual void Tick(float DeltaTime) override;

private:
	TWeakPtr<SnakeGame::Snake> Snake;
	uint32 CellSize;
	SnakeGame::Dim Dims;

	UPROPERTY()
	TArray<ASG_SnakeLink*> SnakeLinks;

	FLinearColor SnakeLinkColor;
};
