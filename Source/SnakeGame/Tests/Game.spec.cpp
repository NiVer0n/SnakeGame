// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "SnakeGame/Core/Game.h"
	#include "SnakeGame/Core/Grid.h"

using namespace SnakeGame;

BEGIN_DEFINE_SPEC(FSnakeGame, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
TUniquePtr<Game> CoreGame;

END_DEFINE_SPEC(FSnakeGame)

void FSnakeGame::Define()
{
	Describe("Core.Game", [this]() {
		BeforeEach(
			[this]()
			{
				Settings GS;
				GS.gridDims = Dim{ 10, 10 };
				GS.snake.startPosition = Grid::center(GS.gridDims.width, GS.gridDims.height);
				CoreGame = MakeUnique<Game>(GS);
			});
		It("GridShouldExist",
			[this]() {
				
				TestTrueExpr(CoreGame->grid().IsValid());
			});
		It("SnakeShouldExist",
			[this]() {
				
				TestTrueExpr(CoreGame->snake().IsValid());
			});
		It("FoodShouldExist",
			[this]() {
				
				TestTrueExpr(CoreGame->food().IsValid());
			});
	});
}

#endif