// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "SnakeGame/Tests/Utils/TestUtils.h"
	#include "SnakeGame/Framework/SG_GameMode.h"
	#include "SnakeGame/Framework/SG_Pawn.h"

BEGIN_DEFINE_SPEC(FSnakeFramework, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
UWorld* World;
END_DEFINE_SPEC(FSnakeFramework)

void FSnakeFramework::Define()
{
	using namespace NiVer0nGames::Test;

	Describe("Framework", [this]() {
		BeforeEach([this]() {
			AutomationOpenMap("GameLevel");
			World = GetTestGameWorld();
		});
		It("GameMapMightExist",
			[this]() 
			{
				TestNotNull("World Exists", World);
			});
		It("ClassesMightBeSetupCorrectly",
			[this]() {
				TestNotNull("Snake GameMode set up", Cast<ASG_GameMode>(World->GetAuthGameMode()));
				TestNotNull("Snake Pawn set up", Cast<ASG_Pawn>(World->GetFirstPlayerController()->GetPawn()));
			});
		xIt("PawnLocationShouldBeAdjustCorrectly",
			[this]() {
				unimplemented();
			});
	});
}

#endif