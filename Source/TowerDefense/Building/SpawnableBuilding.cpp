// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableBuilding.h"
#include "../HealthComponent.h"

ASpawnableBuilding::ASpawnableBuilding()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

UHealthComponent* ASpawnableBuilding::GetHealthComponent() const
{
	return HealthComponent;
}
