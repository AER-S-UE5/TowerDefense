// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingWidget.generated.h"

class ASpawnableBuilding;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBuildingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Populate();

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Buildings")
	TArray<TSubclassOf<class ASpawnableBuilding>> SpawnableBuildings;

	UPROPERTY(EditDefaultsOnly, Category = "Elements")
	TSubclassOf<class UBuildButton> BuildButtonClass;

	UPROPERTY(meta =(BindWidget))
	class UHorizontalBox* BuildingsBox;
};
