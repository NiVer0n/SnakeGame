// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Core/Game.h"
#include "SG_GameMode.generated.h"

class ASG_Grid;
class ASG_Snake;
class AExponentialHeightFog;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class SNAKEGAME_API ASG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASG_GameMode();

	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;


protected:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
	FUintPoint GridDims{ 10, 10 };

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "10", ClampMax = "100"), Category = "Settings")
	uint32 CellSize{ 10 };

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "4", ClampMax = "10"), Category = "Settings")
	uint32 SnakeDefaultSize{ 5 };
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.01", ClampMax = "10"), Category = "Settings")
	float GameSpeed{ 1.0f };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASG_Grid> GridVisualClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASG_Snake> SnakeVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "Design")
	TObjectPtr<UDataTable> ColorsTable;

	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputAction> MoveForwardInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputAction> MoveRightInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputAction> ResetGameInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "SnakeInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

private:
	void UpdateColors();

	void FindFog();

	void SetupInput();
	void OnMoveForward(const FInputActionValue& Value);
	void OnMoveRight(const FInputActionValue& Value);
	void OnGameReset(const FInputActionValue& Value);
	
	SnakeGame::Settings MakeSettings() const;

	UFUNCTION(Exec, Category = "ConsoleCommand")
	void NextColor();

	UPROPERTY()
	ASG_Grid* GridVisual;
	
	UPROPERTY()
	ASG_Snake* SnakeVisual;

	UPROPERTY()
	AExponentialHeightFog* Fog;

	TUniquePtr<SnakeGame::Game> Game;

	uint32 ColorTableIndex{ 0 };

	SnakeGame::Input SnakeInput{ 1, 0 };
};
