// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableBuilding.h"
#include "TurretBase.generated.h"

class USphereComponent;
class AEnemy;
/**
 * 
 */
UCLASS(Abstract)
class TOWERDEFENSE_API ATurretBase : public ASpawnableBuilding
{
	GENERATED_BODY()

public:
	ATurretBase();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	TArray<AEnemy*> GetInRangeEnemies() const;

	USceneComponent* GetFiringPoint()const;

	float GetDamage() const;

	AEnemy* GetTarget()const;

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Radar;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* FiringPoint;

	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float Damage = 30;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	TArray<AEnemy*> InRangeEnemies;

	virtual void Fire() PURE_VIRTUAL(&ATurretBase::Fire, );

	bool IsEnemyInRange() const;

	void LookAtEnemy(AEnemy* Enemy);

	void Attack();

	AEnemy* Target;
};
