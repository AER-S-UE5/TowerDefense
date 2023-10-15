// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleEnemy.h"
#include "../Paths/Path.h"
#include "../Terrain/RoadTerrainTile.h"
#include "Kismet/GameplayStatics.h"
#include "../Building/TargetTower.h"

ASimpleEnemy::ASimpleEnemy()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = Mesh;

}

void ASimpleEnemy::FollowPath()
{
	if (GetPath())
	{
		FVector Destination = (GetPathPointIndex() != -1) ? GetPath()->GetPathPoints()[GetPathPointIndex()]->GetActorLocation():GetPath()->GetTargetTower()->GetActorLocation();
		Destination.Z = GetActorLocation().Z;
		FVector MovementDirection = Destination - GetActorLocation();
		MovementDirection = MovementDirection.GetSafeNormal();
		AddActorWorldOffset(MovementDirection * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), false);
		if (FVector::Distance(GetActorLocation(), Destination) < GetPrecision())
		{
			if (GetPathPointIndex() < GetPath()->GetPathPoints().Num()-1 && GetPathPointIndex()!=-1)
			{
				SetPathPointPointIndex(GetPathPointIndex()+1);
			}
			else
			{
				SetPathPointPointIndex(-1);
			}

		}
	}
}

void ASimpleEnemy::Tick(float DeltaTime)
{
	FollowPath();
}

void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	SetPathPointPointIndex(0);
}

