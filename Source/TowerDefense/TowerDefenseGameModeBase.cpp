// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"
#include "Widgets/BuildingWidget.h"
#include "Building/SpawnableBuilding.h"
#include "Building/SpawnerTower.h"
#include "Terrain/BuildingTerrainTile.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"


ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerDefenseGameModeBase::CreateBuildingWidget()
{
	
	BuildingWidget = Cast<UBuildingWidget>(CreateWidget(GetWorld(), BuildingWidgetClass, "BuildingWidget"));
	BuildingWidget->SetGameMode(this);
}

void ATowerDefenseGameModeBase::HideWidget(UUserWidget* WidgetToHide)
{
	WidgetToHide->RemoveFromParent();
}

void ATowerDefenseGameModeBase::ShowWidget(UUserWidget* WidgetToShow)
{
	WidgetToShow->AddToViewport();
}

UBuildingWidget* ATowerDefenseGameModeBase::GetBuildingWidget() const
{
	return BuildingWidget;
}

void ATowerDefenseGameModeBase::Build(TSubclassOf<ASpawnableBuilding> BuildingClass, ABuildingTerrainTile* TileToBuildOn)
{
	USceneComponent* SpawnPoint = BuildingWidget->GetTileToBuildOn()->GetBuildingPoint();
	GetWorld()->SpawnActor<ASpawnableBuilding>(BuildingClass, SpawnPoint->GetComponentLocation(),SpawnPoint->GetComponentRotation());
	HideWidget(BuildingWidget);
	Player->SetPlayerState(APlayerPawn::PlayerState::Default);
}

void ATowerDefenseGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsGameLost())
	{
		UE_LOG(LogTemp, Warning, TEXT("GameLost..."));
		return;
	}

	if (IsGameWon())
	{
		UE_LOG(LogTemp, Warning, TEXT("GameWon..."));
		return;
	}

	if (CurrentWaveIndex >= EnemiesWaves.Num()) return;
	HandleEnemiesSpawning(DeltaSeconds);
	HandleEnemiesWaves(DeltaSeconds);
}

void ATowerDefenseGameModeBase::DeacrementEnemiesCount()
{
	--EnemiesCount;
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	SpawnerTower =Cast<ASpawnerTower>(UGameplayStatics::GetActorOfClass(this, SpawnerTowerClass));
	TargetTower = Cast<ATargetTower>(UGameplayStatics::GetActorOfClass(this, TargetTowerClass));
	EnemiesCount = 0;
	EnemyWaveTimer = 0;
	EnemySpawningTimer = 0;
	CurrentWaveIndex = 0;
	CurrentEnemyIndex = 0;
	EnemySpawningInterval = Levels[CurrentLevelIndex].EnemiesWaves[CurrentWaveIndex].SpawningRate;
	EnemyWaveLength = Levels[CurrentLevelIndex].EnemiesWaves[CurrentWaveIndex].WaveLength;
	CreateBuildingWidget();
	InitilizeWaves();
	InitilizeWavesEnemies();
}

void ATowerDefenseGameModeBase::InitilizeWaves()
{
	EnemiesWaves.Empty();
	for (auto Wave : Levels[CurrentLevelIndex].EnemiesWaves)
	{
		EnemiesWaves.Emplace(Wave);
	}
}

void ATowerDefenseGameModeBase::InitilizeWavesEnemies()
{
	WaveEnemies.Empty();
	TArray<TSubclassOf<AEnemy>> Enemies;
	EnemiesWaves[CurrentWaveIndex].EnemiesToSpawn.GetKeys(Enemies);
	for (auto Enemy : Enemies)
	{
		WaveEnemies.Add(Enemy, EnemiesWaves[CurrentWaveIndex].EnemiesToSpawn[Enemy]);
	}
}

void ATowerDefenseGameModeBase::HandleEnemiesWaves(float DeltaSeconds)
{
	if (EnemyWaveTimer >= EnemyWaveLength)
	{
		++CurrentWaveIndex;
		if (CurrentWaveIndex >= EnemiesWaves.Num()) return;
		EnemyWaveTimer = 0;
		EnemySpawningInterval = Levels[CurrentLevelIndex].EnemiesWaves[CurrentWaveIndex].SpawningRate;
		EnemyWaveLength = Levels[CurrentLevelIndex].EnemiesWaves[CurrentWaveIndex].WaveLength;
		InitilizeWavesEnemies();
	}
	else
	{
		EnemyWaveTimer += DeltaSeconds;
	}
}

void ATowerDefenseGameModeBase::HandleEnemiesSpawning(float DeltaSeconds)
{
	if (EnemySpawningTimer >= EnemySpawningInterval)
	{
		if (SpawnerTower && WaveEnemies.Num()>0)
		{
			EnemySpawningTimer = 0;
			TSubclassOf<AEnemy> EnemyClass = WaveEnemies.CreateConstIterator().Key();
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

bool ATowerDefenseGameModeBase::IsGameLost()
{
	return (!(TargetTower->IsSafe()));
}

bool ATowerDefenseGameModeBase::IsGameWon()
{
	bool FirstCondition = CurrentWaveIndex >= EnemiesWaves.Num() && TargetTower->IsSafe();
	bool SecondCondition = CurrentWaveIndex == EnemiesWaves.Num() - 1 && EnemiesWaves.Num() == 0 && EnemiesCount<=0 ;
	return(FirstCondition || SecondCondition);
}
