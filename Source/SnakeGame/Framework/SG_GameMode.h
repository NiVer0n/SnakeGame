// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/Game.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;
class AExponentialHeightFog;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"))
	FUintPoint GridDims{ 10, 10 };

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"))
	uint32 CellSize{ 10 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASG_Grid> GridVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	UDataTable* ColorsTable;

private:
	void UpdateColors();
	
	void FindFog();

	UFUNCTION(Exec, Category = "ConsoleCommand")
	void NextColor();

	UPROPERTY()
	ASG_Grid* GridVisual;

	UPROPERTY()
	AExponentialHeightFog* Fog;
	
	TUniquePtr<SnakeGame::Game> Game;

	uint32 ColorTableIndex{0};
};
