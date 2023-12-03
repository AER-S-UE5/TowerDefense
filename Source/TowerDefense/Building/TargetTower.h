// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TargetTower.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API ATargetTower : public ATower
{
	GENERATED_BODY()
public:
	bool IsSafe();
	void Breach();

protected:
	virtual void BeginPlay() override;
private:

	bool bSafe;

};
