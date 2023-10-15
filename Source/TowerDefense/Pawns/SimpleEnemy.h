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

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	float Speed =100;
};
