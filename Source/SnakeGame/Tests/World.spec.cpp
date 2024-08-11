// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "SnakeGame/Tests/Utils/TestUtils.h"
	#include "SnakeGame/World/SG_Grid.h"
	#include "Kismet/GameplayStatics.h"

BEGIN_DEFINE_SPEC(FSnakeWorld, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
END_DEFINE_SPEC(FSnakeWorld)

void FSnakeWorld::Define()
{
	using namespace NiVer0nGames::Test;

	Describe("WorldGrid", [this]() {
		BeforeEach([this]() {
			AutomationOpenMap("GameLevel");
			World = GetTestGameWorld();
		});
		It("OnlyOneValidGridActorShouldExist",
			[this]() {
				TArray<AActor*> Grids;
				UGameplayStatics::GetAllActorsOfClass(World, ASG_Grid::StaticClass(), Grids);
				TestTrueExpr(Grids.Num() == 1);
				TestNotNull("Grid actor exists", Grids[0]);
			});
	});
}

#endif