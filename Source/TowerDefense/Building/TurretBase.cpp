// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBase.h"
#include "Components/SphereComponent.h"
#include "../Pawns/Enemy.h"

ATurretBase::ATurretBase()
{
	Radar = CreateDefaultSubobject<USphereComponent>(TEXT("Radar"));
	RootComponent = Radar;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	FiringPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Firing Point"));
	FiringPoint->SetupAttachment(TurretMesh);


}

void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsEnemyInRange())
	{
		Target = InRangeEnemies[0];
		LookAtEnemy(Target);
	}
	else
	{
		Target = nullptr;
	}
}

void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	Radar->OnComponentBeginOverlap.AddDynamic(this, &ATurretBase::OnOverlapBegin);
	Radar->OnComponentEndOverlap.AddDynamic(this, &ATurretBase::OnOverlapEnd);

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurretBase::Attack, FireRate, true);
	
}


TArray<AEnemy*> ATurretBase::GetInRangeEnemies() const
{
	return InRangeEnemies;
}

USceneComponent* ATurretBase::GetFiringPoint() const
{
	return FiringPoint;
}

float ATurretBase::GetDamage() const
{
	return Damage;
}

AEnemy* ATurretBase::GetTarget() const
{
	return Target;
}

void ATurretBase::OnOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemy* NewEnemy = Cast<AEnemy>(OtherActor))
	{
		InRangeEnemies.Add(NewEnemy);
	}
}

void ATurretBase::OnOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (AEnemy* LeavingEnemy = Cast<AEnemy>(OtherActor))
	{
		InRangeEnemies.Remove(LeavingEnemy);
	}
}

bool ATurretBase::IsEnemyInRange() const
{
	return (InRangeEnemies.Num() > 0);
}

void ATurretBase::LookAtEnemy(AEnemy* Enemy)
{
	FVector LookAtDirection = Enemy->GetActorLocation() - GetActorLocation();
	LookAtDirection.Z = 0;
	TurretMesh->SetRelativeRotation(LookAtDirection.Rotation());
}

void ATurretBase::Attack()
{
	if (IsEnemyInRange())
	{
		Fire();
	}
}
