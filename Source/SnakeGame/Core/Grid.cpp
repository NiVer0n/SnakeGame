// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "Core/Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogGrid, All, All);

using namespace SnakeGame;

Grid::Grid(const Dim& dim, const IPositionRandomizerPtr& randomizer)
	: c_dim(Dim{ dim.width + 2, dim.height + 2 }), m_positionRandomizer(randomizer)
{
	m_cells.Init(CellType::Empty, c_dim.width * c_dim.height);
	initWalls();
	printDebug();
}

void Grid::initWalls()
{
	for (uint32 y = 0; y < c_dim.height; ++y)
	{
		for (uint32 x = 0; x < c_dim.width; ++x)
		{
			if (x == 0 || x == c_dim.width - 1 || y == 0 || y == c_dim.height - 1)
			{
				const auto index = positionToIndex(x, y);
				m_cells[index] = CellType::Wall;
				m_indexByType[CellType::Wall].Add(index);
			}
		}
	}
}

void Grid::freeCellsByType(CellType cellType)
{
	for (int32 i = 0; i < m_indexByType[cellType].Num(); ++i)
	{
		const uint32 index = m_indexByType[cellType][i];
		m_cells[index] = CellType::Empty;
	}
	m_indexByType[cellType].Empty();
}



bool Grid::hitTest(const Position& position, CellType cellType) const
{
	return m_cells[positionToIndex(position)] == cellType;
}

bool Grid::randomEmptyPosition(Position& position) const
{
	return m_positionRandomizer->generatePosition(c_dim, m_cells, position);
}

void Grid::update(const TPositionPtr* links, CellType cellType)
{
	freeCellsByType(cellType);

	auto* link = links;
	while (link)
	{
		updateInternal(link->GetValue(), cellType);
		link = link->GetNextNode();
	}
}

void SnakeGame::Grid::update(const Position& position, CellType cellType)
{
	freeCellsByType(cellType);
	updateInternal(position, cellType);
}

void SnakeGame::Grid::updateInternal(const Position& position, CellType cellType)
{
	const auto index = positionToIndex(position);
	m_cells[index] = cellType;
	m_indexByType[cellType].Add(index);
}

void Grid::printDebug()
{
#if !UE_BUILD_SHIPPING
	for (uint32 y = 0; y < c_dim.height; ++y)
	{
		FString line;
		for (uint32 x = 0; x < c_dim.width; ++x)
		{
			TCHAR symbol{};
			switch (m_cells[positionToIndex(x, y)])
			{
				case CellType::Empty:
				{
					symbol = '0';
					break;
				}
				case CellType::Wall:
				{
					symbol = '*';
					break;
				}
				case CellType::Snake:
				{
					symbol = '_';
					break;
				}
				case CellType::Food:
				{
					symbol = 'F';
					break;
				}
			}
			line.AppendChar(symbol).AppendChar(' ');
		}
		UE_LOG(LogGrid, Display, TEXT("%s"), *line);
	}
#endif
}

uint32 Grid::positionToIndex(uint32 x, uint32 y) const
{
	return x + y * c_dim.width;
}

uint32 Grid::positionToIndex(const Position& position) const
{
	return positionToIndex(position.x, position.y);
}
