// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingWidget.generated.h"

class ASpawnableBuilding;
class ATowerDefenseGameModeBase;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBuildingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Populate();
	void SetTileToBuildOn(class ABuildingTerrainTile* value);
	ABuildingTerrainTile* GetTileToBuildOn() const;
	void Build(TSubclassOf<ASpawnableBuilding> BuildingClass);
	void SetGameMode(ATowerDefenseGameModeBase* value);


protected:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Buildings")
	TMap<TSubclassOf<ASpawnableBuilding>, class UTexture2D* > SpawnableBuildings;

	UPROPERTY(EditDefaultsOnly, Category = "Elements")
	TSubclassOf<class UBuildButton> BuildButtonClass;


	UPROPERTY(meta =(BindWidget))
	class UHorizontalBox* BuildingsBox;

	ABuildingTerrainTile* TileToBuildOn;

	ATowerDefenseGameModeBase* TDGameMode;
};
