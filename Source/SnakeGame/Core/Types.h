// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Containers/List.h"

namespace SnakeGame
{
	struct SNAKEGAME_API Dim
	{
		uint32 width;
		uint32 height;
	};

	struct SNAKEGAME_API Position
	{
		Position(uint32 inX, uint32 inY)
			: x(inX), y(inY) {}

		Position() = default;

		uint32 x{ 0 };
		uint32 y{ 0 };

		FORCEINLINE Position& operator+=(const Position& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		FORCEINLINE bool operator==(const Position& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		static const Position Zero;
	};

	struct SNAKEGAME_API Input
	{
		int8 x;
		int8 y;

		FORCEINLINE bool opposite(const Input& rhs) const
		{
			return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
		}

		static const Input Default;
	};

	enum class CellType
	{
		Empty = 0,
		Wall,
		Snake,
		Food
	};

	struct SNAKEGAME_API Settings
	{
		Dim gridDims{ 40, 10 };
		struct Snake
		{
			uint32 defaultSize{ 4 };
			Position startPosition{ Position::Zero };
		} snake;

		float gameSpeed{ 1.0f };
	};

	using TSnakeList = TDoubleLinkedList<Position>;
	using TPositionPtr = TSnakeList::TDoubleLinkedListNode;

	enum class GameplayEvent
	{
		GameOver = 0,
		GameCompleted,
		FoodTaken
	};

	using GameplayEventCallback = TFunction<void(GameplayEvent)>;
} // namespace SnakeGame