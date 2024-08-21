// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Types.h"
#include "SG_Grid.generated.h"

namespace SnakeGame
{
	class Grid;
} // namespace SnakeGame

struct FSnakeColors;

UCLASS()
class SNAKEGAME_API ASG_Grid : public AActor
{
	GENERATED_BODY()

public:
	ASG_Grid();

	virtual void Tick(float DeltaTime) override;

	/**
	 * Set core model to be observed by the grid world actor
	 * @param Grid  model object
	 * @param CellSize  world size of the cell
	 */
	void SetModel(const TSharedPtr<SnakeGame::Grid>& Grid, uint32 InCellSize);

	void UpdateColors(const FSnakeColors& Colors);

	void Hide();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GridMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* GridMaterial;

private:
	void DrawGrid();

	SnakeGame::Dim GridDim;
	uint32 CellSize;
	uint32 WorldWidth;
	uint32 WorldHeight;
};
