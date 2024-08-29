// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "Framework/SG_GameUserSettings.h"

USG_GameUserSettings::USG_GameUserSettings()
{
	check(GameSpeeds.Num() == StaticEnum<EGameSpeed>()->NumEnums() - 1);
	check(GridSizes.Num() == StaticEnum<EGridSize>()->NumEnums() - 1);
}

USG_GameUserSettings* USG_GameUserSettings::Get()
{
	return GEngine ? Cast<USG_GameUserSettings>(GEngine->GetGameUserSettings()) : nullptr;
}

void USG_GameUserSettings::SaveSnakeSettings(EGameSpeed GameSpeed, EGridSize GridSize)
{
	if (GameSpeeds.Contains(GameSpeed))
	{
		CurrentSpeed = GameSpeeds[GameSpeed];
	}
	if (GridSizes.Contains(GridSize))
	{
		CurrentGridSize = GridSizes[GridSize];
	}
}
