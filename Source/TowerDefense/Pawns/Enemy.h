// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class APath;

UCLASS(Abstract, NotBlueprintable)
class TOWERDEFENSE_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void FollowPath() PURE_VIRTUAL(AEnemy::FollowPath, );
	void SetPath(APath* NewPath);

private:
	void GetNextDestination();
	virtual void Die() PURE_VIRTUAL(AEnemy::Die, );

private:
	UPROPERTY(VisibleAnywhere);
	APath* Path;

	UPROPERTY(EditDefaultsOnly)
	float LocationPrecision = 0.1f;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float GetPrecision() const;
	APath* GetPath() const;

public:	
	// Called every frame
	
	
};
