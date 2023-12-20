// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MaiMenuGameMode.generated.h"

class UMainMenuWidget;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AMaiMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	UMainMenuWidget* MainMenu;

	
};
