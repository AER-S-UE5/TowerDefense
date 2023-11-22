// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TerrainTilesBase.h"
#include "BuildingTerrainTile.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ABuildingTerrainTile : public ATerrainTilesBase
{
	GENERATED_BODY()

public:
	ABuildingTerrainTile();

	void OutlineTile(bool value);

	USceneComponent* GetBuildingPoint() const;
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BuildingPoint;


};
