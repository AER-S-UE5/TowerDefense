// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainTilesBase.h"

// Sets default values
ATerrainTilesBase::ATerrainTilesBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	RootComponent = TileMesh;
}

// Called when the game starts or when spawned
void ATerrainTilesBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainTilesBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

