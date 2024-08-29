// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_MenuHUD.generated.h"

class USG_StartGameWidget;

UCLASS()
class SNAKEGAME_API ASG_MenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_StartGameWidget> StartGameWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<USG_StartGameWidget> StartGameWidget;
};
