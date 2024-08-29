// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "UI/SG_GameOverWidget.h"
#include "Components/TextBlock.h"
#include "World/SG_WorldUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USG_GameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	check(BackToMenuButton);
	BackToMenuButton->OnClicked.AddDynamic(this, &ThisClass::OnBackToMenu);
}

void USG_GameOverWidget::SetScore(uint32 InScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(SnakeGame::WorldUtils::FormatScore(InScore));
	}
}

void USG_GameOverWidget::SetResetKeyName(const FString& ResetGameKeyName)
{
	if (ResetGameText)
	{
		const FString ResetGameInfo = FString::Printf(TEXT("press <%s> to reset"), *ResetGameKeyName.ToLower());
		ResetGameText->SetText(FText::FromString(ResetGameInfo));
	}
}

void USG_GameOverWidget::OnBackToMenu()
{
	if (!MenuLevel.IsNull())
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(MenuLevel.GetAssetName()));
	}
}
