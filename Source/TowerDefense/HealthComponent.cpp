// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Pawns/Enemy.h"
#include "Building/SpawnableBuilding.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UHealthComponent::DecreaseHealth(float Amount)
{
	if (bIsAlive)
	{
		Health -= Amount;
		if (Health < 0)
		{
			Health = 0;
			bIsAlive = false;
		}
	}
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	Health = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Health = %f"),Health);
	bIsAlive = true;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* CausingDamageActor)
{
	if (DamagedActor == GetOwner())
	{
		DecreaseHealth(Damage);
	}
	if (!bIsAlive)
	{
		if (AEnemy* Enemy = Cast<AEnemy>(GetOwner()))
		{
			Enemy->Die();
		}
		else if (ASpawnableBuilding* Building = Cast<ASpawnableBuilding>(GetOwner()))
		{
			Building->DestroyBuilding();
		}
	}
}

float UHealthComponent::GetHealthPercentage() const
{
	float Percentage = Health / MaxHealth;
	return Percentage;
}


