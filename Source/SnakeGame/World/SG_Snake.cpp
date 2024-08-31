// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#include "World/SG_Snake.h"
#include "World/SG_SnakeLink.h"
#include "World/SG_WorldTypes.h"
#include "World/SG_WorldUtils.h"
#include "World/SG_SnakeObjectPool.h"

namespace
{
	constexpr uint32 ReservedSnakeLinksNum = 10;
}

ASG_Snake::ASG_Snake()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASG_Snake::SetModel(const TSharedPtr<SnakeGame::Snake>& InSnake, uint32 InCellSize, const SnakeGame::Dim& InDims)
{
	InitObjectPool();

	Snake = InSnake;
	CellSize = InCellSize;
	Dims = InDims;

	for (auto LinkActor : SnakeLinks)
	{
		ObjectPool->Add<ASG_SnakeLink>(LinkActor);
	}
	SnakeLinks.Empty();

	if (!Snake.IsValid() || !GetWorld())
	{
		return;
	}

	const auto& Links = Snake.Pin()->links();
	for (const auto& Link : Links)
	{
		const FTransform Transform = FTransform(SnakeGame::WorldUtils::LinkPositionToVector(Link, CellSize, Dims));
		auto* LinkActor = ObjectPool->Pop<ASG_SnakeLink>(GetWorld(), Transform, SnakeLinkClass);
		check(LinkActor);
		LinkActor->UpdateScale(CellSize);
		SnakeLinks.Add(LinkActor);
	}
}

void ASG_Snake::InitObjectPool()
{
	if (ObjectPool)
	{
		return;
	}

	ObjectPool = NewObject<USG_SnakeObjectPool>();
	check(ObjectPool);
	ObjectPool->Reserve<ASG_SnakeLink>(GetWorld(), ReservedSnakeLinksNum, SnakeLinkClass);
}

void ASG_Snake::UpdateColors(const FSnakeColors& Colors)
{
	SnakeLinkColor = Colors.SnakeLinkColor;
	for (int i = 0; i < SnakeLinks.Num(); ++i)
	{
		SnakeLinks[i]->UpdateColor(i == 0 ? Colors.SnakeHeadColor : Colors.SnakeLinkColor);
	}
}

void ASG_Snake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Snake.IsValid())
	{
		return;
	}

	const auto& Links = Snake.Pin()->links();
	auto* LinkPtr = Links.GetHead();

	for (auto LinkActor : SnakeLinks)
	{
		LinkActor->SetActorLocation(SnakeGame::WorldUtils::LinkPositionToVector(LinkPtr->GetValue(), CellSize, Dims));
		LinkPtr = LinkPtr->GetNextNode();
	}

	// add links if snake ate food
	while (LinkPtr)
	{
		const FTransform Transform = FTransform(SnakeGame::WorldUtils::LinkPositionToVector(LinkPtr->GetValue(), CellSize, Dims));
		auto* LinkActor = ObjectPool->Pop<ASG_SnakeLink>(GetWorld(), Transform, SnakeLinkClass);
		check(LinkActor);
		LinkActor->UpdateScale(CellSize);
		LinkActor->UpdateColor(SnakeLinkColor);
		SnakeLinks.Add(LinkActor);
		LinkPtr = LinkPtr->GetNextNode();
	}
}

void ASG_Snake::Explode()
{
	for (auto LinkActor : SnakeLinks)
	{
		LinkActor->Explode();
	}
}