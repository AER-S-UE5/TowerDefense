// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretBase.h"
#include "MachineGunTurret.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API AMachineGunTurret : public ATurretBase
{
	GENERATED_BODY()

public:
	virtual void DestroyBuilding() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UNiagaraSystem* FiringParticleSystem;

	

	virtual void Fire() override;

};
