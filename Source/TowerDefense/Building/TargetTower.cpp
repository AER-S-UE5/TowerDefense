// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetTower.h"

bool ATargetTower::IsSafe()
{
	return bSafe;
}

void ATargetTower::Breach()
{
	bSafe = false;
}

void ATargetTower::BeginPlay()
{
	Super::BeginPlay();
	bSafe = true;
}
