// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "../Paths/Path.h"
#include "../HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../TowerDefenseGameModeBase.h"
#include "TowerDefense/Components/PlayerResourcesManager.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Compoennt"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetPath(APath* NewPath)
{
	Path = NewPath;
}

UHealthComponent* AEnemy::GetHealthComponent() const
{
	return HealthComponent;
}

APath* AEnemy::GetPath() const
{
	return Path;
}

void AEnemy::ClaimWorth() const
{
	if(!Worth.IsEmpty() && GameMode->GetResourcesManager())
	{
		TArray<TEnumAsByte<PlayerResource>> Resources;
		Worth.GetKeys(Resources);
		for (auto Resource : Resources)
		{
			GameMode->GetResourcesManager()->AddPlayerResource(Resource,Worth[Resource]);
		}		
	}
	GameMode->GetResourcesManager()->ResourcesUpdated.Broadcast();
}

ATowerDefenseGameModeBase* AEnemy::GetGameMode()
{
	return GameMode;
}

float AEnemy::GetPrecision() const
{
	return LocationPrecision;
}





