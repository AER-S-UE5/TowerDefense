// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerTower.h"

ASpawnerTower::ASpawnerTower()
{
	SpawningPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawning Point"));
	SpawningPoint->SetupAttachment(RootComponent);
}
