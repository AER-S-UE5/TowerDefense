// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "SpawnerTower.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API ASpawnerTower : public ATower
{
	GENERATED_BODY()

public:
	ASpawnerTower();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawningPoint;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(EditInstanceOnly)
	class APath* ArmyPath;

private:
	void SpawnEnemy(APath* PassedPath);

};
