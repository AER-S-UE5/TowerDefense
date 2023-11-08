// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "SimpleEnemy.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API ASimpleEnemy : public AEnemy
{
	GENERATED_BODY()
public:
	ASimpleEnemy();

	virtual void FollowPath() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Die() override;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	float Speed =100;

	UPROPERTY(VisibleAnywhere)
	int32 PathPointIndex;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);

private:
	void UpdatePathPointIndex();
	void MoveTowards(FVector Destination);
};
