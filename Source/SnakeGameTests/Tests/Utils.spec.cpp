// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "SnakeGame/Core/Utils.h"
	#include "SnakeGame/Core/Grid.h"

BEGIN_DEFINE_SPEC(FPositionRandomizer, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::StressFilter | EAutomationTestFlags::HighPriority)

END_DEFINE_SPEC(FPositionRandomizer)

void FPositionRandomizer::Define()
{
	Describe("PositionRandomizer", [this]() 
	{
		It("FreeCellShouldBeFounded",
			[this]() {
				using namespace SnakeGame;
				const auto Randomizer = MakeShared<PositionRandomizer>();
				const Dim Dimentions{ 10, 10 };
				auto TestGrid = MakeShared<Grid>(Dimentions, Randomizer);

				Position Pos;
				for (uint32 i = 0; i < 1000; ++i)
				{
					const bool Result = TestGrid->randomEmptyPosition(Pos);
					TestTrueExpr(Result);
					TestTrueExpr(Pos.x >= 1 && Pos.x <= Dimentions.width);
					TestTrueExpr(Pos.y >= 1 && Pos.y <= Dimentions.height);
				}
			});
	});
}

#endif