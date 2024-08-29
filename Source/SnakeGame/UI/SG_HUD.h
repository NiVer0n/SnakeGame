// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_HUD.generated.h"

class USG_GameplayWidget;
class USG_GameOverWidget;

UENUM()
enum class EUIGameState : uint8
{
	GameInProgress = 0,
	GameOver,
	GameCompleted
};

namespace SnakeGame
{
	class Game;
}

UCLASS()
class SNAKEGAME_API ASG_HUD : public AHUD
{
	GENERATED_BODY()

public:
	ASG_HUD();

	virtual void Tick(float DeltaSeconds) override;
	
	void SetModel(const TSharedPtr<SnakeGame::Game>& InGame);

	void SetInputKeyNames(const FString& ResetGameKeyName);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_GameplayWidget> GameplayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_GameOverWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	void SetUIGameState(EUIGameState InGameState);
	
	UPROPERTY()
	TObjectPtr<USG_GameplayWidget> GameplayWidget;
	
	UPROPERTY()
	TObjectPtr<USG_GameOverWidget> GameOverWidget;

	TWeakPtr<SnakeGame::Game> Game;
	
	EUIGameState GameState;

	UPROPERTY()
	TMap<EUIGameState, TObjectPtr<UUserWidget>> GameWidgets;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentWidget;
};
