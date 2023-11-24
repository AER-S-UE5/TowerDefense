// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Wave.generated.h"

/**
 * 
 */
USTRUCT()
struct FWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<class AEnemy>, int32> EnemiesToSpawn;

	UPROPERTY(EditAnywhere)
	float SpawningRate = 0.1f;

	UPROPERTY(EditAnywhere)
	float WaveLength = 25;

	FWave()
	{

	}
};
