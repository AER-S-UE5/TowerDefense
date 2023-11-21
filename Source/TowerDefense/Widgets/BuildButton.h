// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildButton.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBuildButton : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta =(BindWidget))
	class UTextBlock* BuildingName;

	UPROPERTY(meta = (BindWidget))
	class UButton* BuildButton;
	
};
