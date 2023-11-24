// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utility/LevelData.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"

class UBuildingWidget;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void CreateBuildingWidget();
	void HideWidget(UUserWidget* WidgetToHide);
	void ShowWidget(UUserWidget* WidgetToShow);
	UBuildingWidget* GetBuildingWidget() const;
	void Build(TSubclassOf<ASpawnableBuilding> BuildingClass,class ABuildingTerrainTile* TileToBuildOn);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category ="Widgets")
	TSubclassOf<UBuildingWidget> BuildingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category ="Levels")
	TArray<FLevelData> Levels;

	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	int32 CurrentLevelIndex = 1;

	UBuildingWidget* BuildingWidget;

	class APlayerPawn* Player;
};
