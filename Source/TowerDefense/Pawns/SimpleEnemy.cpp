// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleEnemy.h"
#include "../Paths/Path.h"
#include "../Terrain/RoadTerrainTile.h"
#include "Kismet/GameplayStatics.h"
#include "../Building/TargetTower.h"
#include "../TowerDefenseGameModeBase.h"
#include "Components/StaticMeshComponent.h"


ASimpleEnemy::ASimpleEnemy()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = Mesh;

}

void ASimpleEnemy::FollowPath()
{
	if (GetPath())
	{
		FVector Destination = (PathPointIndex != -1) ? GetPath()->GetPathPoints()[PathPointIndex]->GetActorLocation() : GetPath()->GetTargetTower()->GetActorLocation();
		Destination.Z = GetActorLocation().Z;
		MoveTowards(Destination);		
		if (FVector::Distance(GetActorLocation(), Destination) < GetPrecision())
		{
			UpdatePathPointIndex();
		}
	}
}

void ASimpleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowPath();
}

void ASimpleEnemy::BeginPlay()
{
	Super::BeginPlay();
	PathPointIndex = 0;
	Mesh->OnComponentHit.AddDynamic(this, &ASimpleEnemy::OnHit);
}

void ASimpleEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (ATargetTower* TargetTower = Cast<ATargetTower>(OtherActor))
	{
		TargetTower->Breach();
		Die();
	}
}

void ASimpleEnemy::UpdatePathPointIndex()
{
	if (PathPointIndex < GetPath()->GetPathPoints().Num()-1 && PathPointIndex!=-1)
	{
		PathPointIndex++;
	}
	else
	{
		PathPointIndex = -1;
	}
}

void ASimpleEnemy::MoveTowards(FVector Destination)
{
	FVector MovementDirection = Destination - GetActorLocation();
	MovementDirection = MovementDirection.GetSafeNormal();
	AddActorWorldOffset(MovementDirection * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ASimpleEnemy::Die()
{
	GetGameMode()->DecrementEnemiesCount();
	ClaimWorth();
	Destroy();
}
