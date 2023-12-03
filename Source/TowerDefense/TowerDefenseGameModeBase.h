// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utility/LevelData.h"
#include "GameFramework/GameModeBase.h"
#include "Utility/Wave.h"
#include "TowerDefenseGameModeBase.generated.h"

class UBuildingWidget;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATowerDefenseGameModeBase();
	void CreateBuildingWidget();
	void HideWidget(UUserWidget* WidgetToHide);
	void ShowWidget(UUserWidget* WidgetToShow);
	UBuildingWidget* GetBuildingWidget() const;
	void Build(TSubclassOf<ASpawnableBuilding> BuildingClass,class ABuildingTerrainTile* TileToBuildOn);
	virtual void Tick(float DeltaSeconds) override;
	void DeacrementEnemiesCount();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
	TSubclassOf<UBuildingWidget> BuildingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category ="Levels")
	TArray<FLevelData> Levels;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 CurrentLevelIndex = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ASpawnerTower> SpawnerTowerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<class ATargetTower> TargetTowerClass;

	UBuildingWidget* BuildingWidget;

	class APlayerPawn* Player;

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

	void InitilizeWaves();
	void InitilizeWavesEnemies();
	void HandleEnemiesWaves(float DeltaSeconds);
	void HandleEnemiesSpawning(float DeltaSeconds);
	bool IsGameLost();
	bool IsGameWon();
};
