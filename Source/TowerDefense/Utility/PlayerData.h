// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.generated.h"

UENUM()
enum PlayerResource
{
	GoldCoins UMETA(DisplayName = "Gold Coins"),
	Power UMETA(DisplayName ="Power")
};
/**
 * 
 */
USTRUCT()
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<PlayerResource>, float> Resources;
	
};
