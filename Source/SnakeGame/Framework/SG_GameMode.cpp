// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "Framework/SG_GameMode.h"
#include "Core/Types.h"
#include "World/SG_Grid.h"
#include "SG_Pawn.h"
#include "Core/Grid.h"

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	// init core game
	const Snake::Settings GS{ GridDims.X, GridDims.Y };
	Game = MakeUnique<Snake::Game>(GS);
	check(Game.IsValid());

	// init and spawn world grid
	const FTransform GridOrigin = FTransform::Identity;
	check(GetWorld());
	GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigin);
	check(GridVisual);
	GridVisual->SetModel(Game->grid(), CellSize);
	GridVisual->FinishSpawning(GridOrigin);

	// set pawn location fitting grid in viewport
	auto* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	auto* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
	check(Pawn);
	check(Game->grid().IsValid());
	Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigin);
}
