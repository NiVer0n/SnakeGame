// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"

namespace Snake
{
	struct Dim
	{
		int32 width;
		int32 height;
	};

	enum class CellType
	{
		Empty = 0,
		Wall
	};

	struct Settings
	{
		Dim gridDims;
	};
}