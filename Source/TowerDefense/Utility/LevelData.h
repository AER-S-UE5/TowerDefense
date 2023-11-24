// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wave.h"
#include "LevelData.generated.h"

/**
 * 
 */
USTRUCT()
struct  FLevelData 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FWave> EnemiesWaves;
	
	FLevelData()
	{

	}
};
