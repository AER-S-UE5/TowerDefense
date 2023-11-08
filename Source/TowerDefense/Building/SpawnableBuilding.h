// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "SpawnableBuilding.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ASpawnableBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	virtual void DestroyBuilding() PURE_VIRTUAL(&ASpawnableBuilding::DestroyBuilding, );
};
