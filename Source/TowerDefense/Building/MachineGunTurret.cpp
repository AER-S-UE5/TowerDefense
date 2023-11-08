// Fill out your copyright notice in the Description page of Project Settings.


#include "MachineGunTurret.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"



void AMachineGunTurret::DestroyBuilding()
{

}

void AMachineGunTurret::Fire()
{
	if (FiringParticleSystem && GetTarget())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FiringParticleSystem, GetFiringPoint()->GetComponentLocation(), GetFiringPoint()->GetComponentRotation());
		UGameplayStatics::ApplyDamage(GetTarget(), GetDamage(), GetInstigatorController(), this, UDamageType::StaticClass());
	}
}
