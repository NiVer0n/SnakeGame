// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameOverWidget.generated.h"

class UTextBlock;

UCLASS()
class SNAKEGAME_API USG_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScore(uint32 InScore);

	void SetResetKeyName(const FString& ResetGameKeyName); 

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;
		
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResetGameText;
};
