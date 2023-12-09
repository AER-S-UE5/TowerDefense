// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefense/Utility/PlayerData.h"
#include "GameTitleBar.generated.h"


class ATowerDefenseGameModeBase;
class UHorizontalBox;
class UResourceDisplay;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameTitleBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetGameMode(ATowerDefenseGameModeBase* value);
	void Populate(TArray<TEnumAsByte<PlayerResource>> Resources);
	
	UFUNCTION()
	void Update();
	
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UResourceDisplay> ResourceDisplayClass;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ResourcesContainer;

	ATowerDefenseGameModeBase* GameMode;
};
