// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "Core/Food.h"
	#include "Core/Types.h"


BEGIN_DEFINE_SPEC(FSnakeFood, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

END_DEFINE_SPEC(FSnakeFood)

void FSnakeFood::Define()
{
	using namespace SnakeGame;
	
	Describe("Core.Food", [this]()
	{
		It("PositionCanBeUpdated",
			[this]()
			{
				const Position position = Position(45, 67);
				Food CoreFood;
				CoreFood.setPosition(position);
				TestTrueExpr(CoreFood.position() == position);
			});
	});
}

#endif