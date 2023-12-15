// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildButton.generated.h"

class ATowerDefenseGameModeBase;
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

	void SetBuildingWidget(class UBuildingWidget* Widget);

	void SetGameMode(ATowerDefenseGameModeBase* Value);

	bool CheckCostAvailability() const;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta =(BindWidget))
	class UTextBlock* BuildingName;

	UPROPERTY(meta = (BindWidget))
	class UButton* BuildButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* BuildingIcon;

	TSubclassOf<ASpawnableBuilding> BuildingClass;

	UPROPERTY()
	class UBuildingWidget* BuildingWidget;

	ATowerDefenseGameModeBase* GameMode;

	UFUNCTION()
	void Build();

	
};
