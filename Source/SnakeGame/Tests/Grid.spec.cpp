// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "SnakeGame/Core/Grid.h"

DEFINE_SPEC(FSnakeGrid, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeGrid::Define()
{
	using namespace Snake;

	Describe("CoreGrid", [this]() {
		It("DimMightIncludeWalls",
			[this]() {
				const Grid grid(Dim{10, 10});
				TestTrueExpr(grid.dim().height == 12);
				TestTrueExpr(grid.dim().width == 12);
			});
	});
}

#endif