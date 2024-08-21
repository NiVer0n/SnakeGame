// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "UI/SG_GameplayWidget.h"
#include "Components/TextBlock.h"
#include "World/SG_WorldUtils.h"

void USG_GameplayWidget::SetGameTime(float InSeconds)
{
	if (TimeText)
	{
		TimeText->SetText(SnakeGame::WorldUtils::FormatSeconds(InSeconds));
	}
}

void USG_GameplayWidget::SetScore(uint32 InScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(InScore));
	}
}

void USG_GameplayWidget::SetResetKeyName(const FString& ResetGameKeyName)
{
	if (ResetGameText)
	{
		const FString ResetGameInfo = FString::Printf(TEXT("press <%s> to reset"), *ResetGameKeyName.ToLower());
		ResetGameText->SetText(FText::FromString(ResetGameInfo));
	}
}
