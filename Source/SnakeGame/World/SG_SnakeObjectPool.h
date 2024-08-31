// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SG_SnakeObjectPool.generated.h"

UCLASS()
class SNAKEGAME_API USG_SnakeObjectPool : public UObject
{
	GENERATED_BODY()

public:
	template <typename ActorType>
	void Reserve(UWorld* World, uint32 Num, const TSubclassOf<AActor>& ActorClass)
	{
		if (!World)
		{
			return;
		}

		for (uint32 i = 0; i < Num; ++i)
		{
			ActorType* Actor = World->SpawnActor<ActorType>(ActorClass, FTransform::Identity);
			Add(Actor);
		}
	}

	template <typename ActorType>
	ActorType* Pop(UWorld* World, const FTransform& Transform, const TSubclassOf<AActor>& ActorClass)
	{
		if (!World)
		{
			return nullptr;
		}

		ActorType* Actor = Pool.IsEmpty() ? World->SpawnActor<ActorType>(ActorClass, Transform) : Cast<ActorType>(Pool.Pop());
		check(Actor);
		Actor->SetActorTransform(Transform);
		Actor->SetActorHiddenInGame(false);
		return Actor;
	}

	template <typename ActorType>
	void Add(ActorType* Actor)
	{
		if (!Actor)
		{
			return;
		}

		Actor->SetActorHiddenInGame(true);
		Pool.Add(Actor);
	}

private:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> Pool;
};
