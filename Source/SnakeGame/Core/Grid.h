// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace Snake
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

	private:
		const Dim c_dim;
		TArray<CellType> m_cells;
		
		void initWalls();
		void printDebug();
		FORCEINLINE uint32 positionToIndex(uint32 x, uint32 y) const;
	};
} // namespace Snake