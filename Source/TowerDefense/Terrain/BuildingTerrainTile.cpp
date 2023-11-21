// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingTerrainTile.h"

ABuildingTerrainTile::ABuildingTerrainTile()
{
	BuildingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Building Point"));
	BuildingPoint->SetupAttachment(RootComponent);
}

void ABuildingTerrainTile::OutlineTile(bool value)
{
	if (!GetTileMesh()) return;
	GetTileMesh()->SetRenderCustomDepth(value);
}
