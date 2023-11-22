// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildButton.generated.h"

class ASpawnableBuilding;

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBuildButton : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetBuildingName(FString value);
	
	void SetBuildingIcon(UTexture2D* value);

	void SetBuildingClass(TSubclassOf<ASpawnableBuilding> value);

private:
	UPROPERTY(meta =(BindWidget))
	class UTextBlock* BuildingName;

	UPROPERTY(meta = (BindWidget))
	class UButton* BuildButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* BuildingIcon;

	TSubclassOf<ASpawnableBuilding> BuildingClass;
	
};
