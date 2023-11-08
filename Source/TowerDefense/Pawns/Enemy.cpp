// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "../Paths/Path.h"
#include "../HealthComponent.h"

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

float AEnemy::GetPrecision() const
{
	return LocationPrecision;
}





