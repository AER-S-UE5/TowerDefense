// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingBase.h"
#include "TowerDefense/Utility/PlayerData.h"
#include "SpawnableBuilding.generated.h"

class UHealthComponent;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ASpawnableBuilding : public ABuildingBase
{
	GENERATED_BODY()

public:
	ASpawnableBuilding();

	virtual void DestroyBuilding() PURE_VIRTUAL(&ASpawnableBuilding::DestroyBuilding, );

	UHealthComponent* GetHealthComponent() const;

	FString GetBuildingClassName() const;

	TMap<TEnumAsByte<PlayerResource>, int32> GetCost() const;

protected:
	void SetClassName(FString value);

private:
	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	FString BuildingClassName;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TMap<TEnumAsByte<PlayerResource>, int32> Cost;
};
