// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDefense/Utility/PlayerData.h"
#include "ResourceDisplay.generated.h"


class UTextBlock;
class UTexture2D;
class UImage;
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UResourceDisplay : public UUserWidget
{
	GENERATED_BODY()
public:
	void Setup(UTexture2D* NewIcon, int32 NewQuantity, PlayerResource Value);
	void Update(int32 NewQuantity) const;
	PlayerResource GetResource() const;
private:
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Quantity;

	PlayerResource Resource;
	
};
