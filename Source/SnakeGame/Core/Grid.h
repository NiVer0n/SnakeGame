// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
	class Grid
	{
	public:
		Grid(const Dim& dim);

		/**
		 * Returns grid dimensions including walls (width + 2; height + 2)
		 * @return Dim  grid dimensions
		 */
		Dim dim() const { return c_dim; };

		void update(const TPositionPtr* links, CellType cellType);

		bool hitTest(const Position& position, CellType cellType) const;

		void printDebug();

	private:
		void initWalls();
		void freeCellsByType(CellType cellType);

		FORCEINLINE uint32 positionToIndex(uint32 x, uint32 y) const;
		FORCEINLINE uint32 positionToIndex(const Position& position) const;

		TArray<CellType> m_cells;
		TMap<CellType, TArray<uint32>> m_indexByType = 
		{
			{ CellType::Snake, {} },
			{ CellType::Wall, {} },
		};
		const Dim c_dim;
	};
} // namespace SnakeGame