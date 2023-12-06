// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayGameModeState.h"

#include "Kismet/GameplayStatics.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"
#include "TowerDefense/Building/SpawnerTower.h"
#include "TowerDefense/Building/TargetTower.h"

void UPlayGameModeState::OnEnter()
{
	Super::OnEnter();
	UGameplayStatics::SetGamePaused(this, false);
}

void UPlayGameModeState::DecrementEnemiesCount()
{
	--EnemiesCount;
}

void UPlayGameModeState::OnExit()
{
	Super::OnExit();
	UGameplayStatics::SetGamePaused(this, true);
}

void UPlayGameModeState::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("PlayGameModeState Updating ..."));
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("CurrentWaveIndex.. %d "), CurrentWaveIndex);
	if (CurrentWaveIndex >= EnemiesWaves.Num()) return;
	HandleEnemiesSpawning(DeltaTime);
	HandleEnemiesWaves(DeltaTime);
}

void UPlayGameModeState::Initialize(ATowerDefenseGameModeBase* ATDGMB,TSubclassOf<ASpawnerTower> AST, TSubclassOf<ATargetTower> ATT, const FLevelData &LevelData )
{
	Super::Initialize(ATDGMB);
	SpawnerTower =Cast<ASpawnerTower>(UGameplayStatics::GetActorOfClass(GetGameMode(), AST));
	if(SpawnerTower)UE_LOG(LogTemp, Warning, TEXT("Spawner Tower Exist..."));
	TargetTower = Cast<ATargetTower>(UGameplayStatics::GetActorOfClass(GetGameMode(), ATT));
	EnemiesCount = 0;
	EnemyWaveTimer = 0;
	EnemySpawningTimer = 0;
	CurrentWaveIndex = 0;
	CurrentEnemyIndex = 0;
	InitializeWaves(LevelData);
	InitializeWavesEnemies();
	EnemySpawningInterval = EnemiesWaves[CurrentWaveIndex].SpawningRate;
	EnemyWaveLength = EnemiesWaves[CurrentWaveIndex].WaveLength;
}

bool UPlayGameModeState::IsGameLost() const
{
	return (!(TargetTower->IsSafe()));
}

bool UPlayGameModeState::IsGameWon() const
{
	const bool FirstCondition = CurrentWaveIndex >= EnemiesWaves.Num() && TargetTower->IsSafe();
	const bool SecondCondition = CurrentWaveIndex == EnemiesWaves.Num() - 1 && EnemiesWaves.Num() == 0 && EnemiesCount<=0 ;
	return(FirstCondition || SecondCondition);
}

void UPlayGameModeState::InitializeWaves(const FLevelData &LevelData)
{
	EnemiesWaves.Empty();
	for( auto Wave : LevelData.EnemiesWaves)
	{
		EnemiesWaves.Emplace(Wave);
	}
}

void UPlayGameModeState::InitializeWavesEnemies()
{
	WaveEnemies.Empty();
	TArray<TSubclassOf<AEnemy>> Enemies;
	EnemiesWaves[CurrentWaveIndex].EnemiesToSpawn.GetKeys(Enemies);
	for( auto Enemy: Enemies)
	{
		WaveEnemies.Add(Enemy, EnemiesWaves[CurrentWaveIndex].EnemiesToSpawn[Enemy]);
	}
}

void UPlayGameModeState::HandleEnemiesWaves(float DeltaSeconds)
{
	if (EnemyWaveTimer >= EnemyWaveLength)
	{
		++CurrentWaveIndex;
		if (CurrentWaveIndex >= EnemiesWaves.Num()) return;
		EnemyWaveTimer = 0;
		EnemySpawningInterval = EnemiesWaves[CurrentWaveIndex].SpawningRate;
		EnemyWaveLength = EnemiesWaves[CurrentWaveIndex].WaveLength;
		InitializeWavesEnemies();
	}
	else
	{
		EnemyWaveTimer += DeltaSeconds;
	}
}

void UPlayGameModeState::HandleEnemiesSpawning(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Spawn Timer %f of %f"),EnemySpawningTimer, EnemySpawningInterval);
	if (EnemySpawningTimer >= EnemySpawningInterval)
	{
		
		if (SpawnerTower && WaveEnemies.Num()>0)
		{
			EnemySpawningTimer = 0;
			const TSubclassOf<AEnemy> EnemyClass = WaveEnemies.CreateConstIterator().Key();
			SpawnerTower->SpawnEnemy(EnemyClass);
			++EnemiesCount;
			if (WaveEnemies[EnemyClass]-1 > 0)
			{
				WaveEnemies.Add(EnemyClass, WaveEnemies[EnemyClass] - 1);
			}
			else
			{
				WaveEnemies.Remove(EnemyClass);
				WaveEnemies.Compact();
				WaveEnemies.Shrink();
			}
		}
	}
	else
	{
		EnemySpawningTimer += DeltaSeconds;
	}
}
