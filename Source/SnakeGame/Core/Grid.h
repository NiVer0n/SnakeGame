// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Utils.h"

namespace SnakeGame
{
	class SNAKEGAME_API Grid
	{
	public:
		Grid(const Dim& dim, const IPositionRandomizerPtr& randomizer = MakeShared<PositionRandomizer>());

		/**
		 * Returns grid dimensions including walls (width + 2; height + 2)
		 * @return Dim  grid dimensions
		 */
		Dim dim() const { return c_dim; };

		void update(const TPositionPtr* links, CellType cellType);
		void update(const Position& position, CellType cellType);

		bool hitTest(const Position& position, CellType cellType) const;

		[[nodiscard]] bool randomEmptyPosition(Position& position) const;

		void printDebug();

		static Position center(uint32 width, uint32 height) { return Position(width / 2 + 1, height / 2 + 1); }

	private:
		void initWalls();
		void freeCellsByType(CellType cellType);
		void updateInternal(const Position& position, CellType cellType);

		FORCEINLINE uint32 positionToIndex(uint32 x, uint32 y) const;
		FORCEINLINE uint32 positionToIndex(const Position& position) const;

		TArray<CellType> m_cells;
		TMap<CellType, TArray<uint32>> m_indexByType = 
		{
			{ CellType::Snake, {} },
			{ CellType::Wall, {} },
			{ CellType::Food, {} },
		};

		const Dim c_dim;
		IPositionRandomizerPtr m_positionRandomizer;
	};
} // namespace SnakeGame