// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "UI/SG_HUD.h"
#include "UI/SG_GameplayWidget.h"
#include "UI/SG_GameOverWidget.h"
#include "Core/Game.h"

void ASG_HUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
	check(GameplayWidget);
	GameWidgets.Add(EUIGameState::GameInProgress, GameplayWidget);

	GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverWidgetClass);
	check(GameOverWidget);
	GameWidgets.Add(EUIGameState::GameOver, GameOverWidget);

	for (auto& [UIState, GameWidget] : GameWidgets)
	{
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
	if (!InGame)
	{
		return;
	}

	using namespace SnakeGame;

	Game = InGame;
	SetUIGameState(EUIGameState::GameInProgress);
	GameplayWidget->SetScore(InGame->score());
	GameOverWidget->SetScore(InGame->score());

	InGame->subscribeOnGameplayEvent([&](GameplayEvent Event) {
		switch (Event)
		{
			case SnakeGame::GameplayEvent::GameCompleted: [[fallthrough]];
			case SnakeGame::GameplayEvent::GameOver:
			{
				GameOverWidget->SetScore(InGame->score());
				SetUIGameState(EUIGameState::GameOver);
				break;
			}
			case SnakeGame::GameplayEvent::FoodTaken:
			{
				GameplayWidget->SetScore(InGame->score());
				break;
			}
		}
	});
}

void ASG_HUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Game.IsValid() && GameState == EUIGameState::GameInProgress)
	{
		GameplayWidget->SetGameTime(Game.Pin()->gameTime());
	}
}

void ASG_HUD::SetUIGameState(EUIGameState InGameState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameWidgets.Contains(GameState))
	{
		CurrentWidget = GameWidgets[GameState];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	GameState = InGameState;
}

void ASG_HUD::SetInputKeyNames(const FString& ResetGameKeyName)
{
	GameplayWidget->SetResetKeyName(ResetGameKeyName);
	GameOverWidget->SetResetKeyName(ResetGameKeyName);
}
