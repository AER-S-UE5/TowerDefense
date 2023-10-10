// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "SpawnerTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ASpawnerTower : public ATower
{
	GENERATED_BODY()

public:
	ASpawnerTower();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawningPoint;
};
