// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeState.h"
#include "../Utility/Wave.h"
#include "../Pawns/Enemy.h"
#include "../Utility/LevelData.h"
#include "PlayGameModeState.generated.h"

class UBuildingWidget;
class APlayerPawn;
class ASpawnerTower;
class ATargetTower;
class AEnemy;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UPlayGameModeState : public UGameModeState
{
	GENERATED_BODY()

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void UpdateTick(float DeltaTime) override;
	void DecrementEnemiesCount();

	void Initialize(ATowerDefenseGameModeBase* ATDGMB, TSubclassOf<ASpawnerTower> AST, TSubclassOf<ATargetTower> ATT, const FLevelData&  LevelData);

	bool IsGameLost() const;
	bool IsGameWon() const;

	

private:

	APlayerPawn* Player;
	ASpawnerTower* SpawnerTower;
	ATargetTower* TargetTower;
	TArray<FWave> EnemiesWaves;
	TMap<TSubclassOf<AEnemy>, int32> WaveEnemies;
	

	float EnemySpawningTimer;
	float EnemySpawningInterval;
	float EnemyWaveTimer;
	float EnemyWaveLength;
	int32 CurrentWaveIndex;
	int32 CurrentEnemyIndex;
	int32 EnemiesCount;

	void InitializeWaves(const FLevelData &LevelData);
	void InitializeWavesEnemies();
	void HandleEnemiesWaves(float DeltaSeconds);
	void HandleEnemiesSpawning(float DeltaSeconds);
};
