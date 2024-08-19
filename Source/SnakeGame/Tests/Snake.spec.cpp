// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#if WITH_AUTOMATION_TESTS

	#include "CoreMinimal.h"
	#include "Misc/AutomationTest.h"
	#include "Core/Snake.h"
	#include "Core/Types.h"

using namespace SnakeGame;

BEGIN_DEFINE_SPEC(FSnake, "Snake",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

TUniquePtr<Snake> CoreSnake;
Settings::Snake Config;

END_DEFINE_SPEC(FSnake)

void FSnake::Define()
{
	Describe("Core.Snake", [this]() {
		BeforeEach(
			[this]()
			{
				Config.defaultSize = 10;
				Config.startPosition = Position(100, 0);
				CoreSnake = MakeUnique<Snake>(Config);
			});
		It("MightBeInitCorrectly",
			[this]()
			{
				Position LinkPosition = Config.startPosition;
				TestTrueExpr(CoreSnake->head() == LinkPosition);
				TestTrueExpr(CoreSnake->links().Num() == Config.defaultSize);

				auto* Link = CoreSnake->links().GetHead();
				while (Link)
				{
					TestTrueExpr(Link->GetValue() == LinkPosition);
					Link = Link->GetNextNode();
					--LinkPosition.x;
				}
			});

		It("Movement.CanBeMovedRight",
			[this]()
			{
				Position LinkPosition = Config.startPosition;
				TestTrueExpr(CoreSnake->head() == LinkPosition);
				CoreSnake->move(Input::Default);

				auto* Link = CoreSnake->links().GetHead();
				while (Link)
				{
					TestTrueExpr(Link->GetValue() == Position(LinkPosition.x + 1, LinkPosition.y));
					Link = Link->GetNextNode();
					--LinkPosition.x;
				}
			});

		It("Movement.CannotBeMovedLeftByDefault",
			[this]()
			{
				Position LinkPosition = Config.startPosition;
				TestTrueExpr(CoreSnake->head() == LinkPosition);
				CoreSnake->move(Input { -1, 0 });

				auto* Link = CoreSnake->links().GetHead();
				while (Link)
				{
					TestTrueExpr(Link->GetValue() == Position(LinkPosition.x + 1, LinkPosition.y));
					Link = Link->GetNextNode();
					--LinkPosition.x;
				}
			});

		It("Movement.CanBeMovedUp",
			[this]() {
				Position LinkPosition = Config.startPosition;
				TestTrueExpr(CoreSnake->head() == LinkPosition);
				CoreSnake->move(Input{ 0, 1 });

				auto* Link = CoreSnake->links().GetHead();
				TestTrueExpr(Link->GetValue() == Position(LinkPosition.x, LinkPosition.y + 1));

				Link = Link->GetNextNode();
				while (Link)
				{
					TestTrueExpr(Link->GetValue() == LinkPosition);
					Link = Link->GetNextNode();
					--LinkPosition.x;
				}
			});
		
		It("Movement.CanBeMovedDown",
			[this]() {
				Position LinkPosition = Config.startPosition;
				TestTrueExpr(CoreSnake->head() == LinkPosition);
				CoreSnake->move(Input{ 0, -1 });

				auto* Link = CoreSnake->links().GetHead();
				TestTrueExpr(Link->GetValue() == Position(LinkPosition.x, LinkPosition.y - 1));

				Link = Link->GetNextNode();
				while (Link)
				{
					TestTrueExpr(Link->GetValue() == LinkPosition);
					Link = Link->GetNextNode();
					--LinkPosition.x;
				}
			});
		
		It("Size.CanBeIncreased",
			[this]()
			{
				for (uint8 i = 0; i < 2; ++i)
				{
					CoreSnake->increase();
					TestTrueExpr(CoreSnake->links().Num() == Config.defaultSize + i + 1);
				}
			});
	});
}

#endif