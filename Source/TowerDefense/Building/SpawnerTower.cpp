// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerTower.h"
#include "../Pawns/Enemy.h"
#include "../Paths/Path.h"
#include "Kismet/GameplayStatics.h"

ASpawnerTower::ASpawnerTower()
{
	SpawningPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawning Point"));
	SpawningPoint->SetupAttachment(RootComponent);
}

void ASpawnerTower::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("%s is ArmyPath Name...."), *(ArmyPath->GetName()));
	FTimerHandle SpawningEnemyTimerHandle;
	FTimerDelegate SpawnEnemyTimerDelegate = FTimerDelegate::CreateUObject(this, &ASpawnerTower::SpawnEnemy, ArmyPath);
	GetWorldTimerManager().SetTimer(SpawningEnemyTimerHandle, SpawnEnemyTimerDelegate, 5, true);
}

void ASpawnerTower::SpawnEnemy(APath* PassedPath)
{
	AEnemy* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemy>(EnemyClass, SpawningPoint->GetComponentTransform());
	NewEnemy->SetPath(PassedPath);
	UGameplayStatics::FinishSpawningActor(NewEnemy, SpawningPoint->GetComponentTransform());

}
