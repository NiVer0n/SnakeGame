// SnakeGame. Copyright NiVer0n Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeGame/Core/Food.h"
#include "SG_Food.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASG_Food : public AActor
{
	GENERATED_BODY()

public:
	ASG_Food();

	void SetModel(const TSharedPtr<SnakeGame::Food>& InFood, uint32 InCellSize, const SnakeGame::Dim& InDims);

	void UpdateColor(const FLinearColor& Color);

	virtual void Tick(float DeltaTime) override;

	void Explode();

	void Hide();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Origin;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> FoodMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;


private:
	FVector GetFoodWorldLocation() const;
	
	TWeakPtr<SnakeGame::Food> Food;
	uint32 CellSize;
	SnakeGame::Dim Dims;
	FLinearColor FoodColor;
};
