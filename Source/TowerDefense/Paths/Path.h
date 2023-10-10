// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Path.generated.h"

class ARoadTerrainTile;
class ATargetTower;

UCLASS()
class TOWERDEFENSE_API APath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APath();

private:
	

	UPROPERTY(EditInstanceOnly, Category = "Trajectory")
	TArray<ARoadTerrainTile*> PathPoints;

	UPROPERTY(EditInstanceOnly, Category = "Trajectory")
	ATargetTower* TargetTower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<ARoadTerrainTile*> GetPathPoints();
	ATargetTower* GetTargetTower();
};
