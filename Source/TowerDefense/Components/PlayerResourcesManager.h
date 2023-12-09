// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerDefense/Utility/PlayerData.h"
#include "PlayerResourcesManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UPlayerResourcesManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerResourcesManager();

	void AddPlayerResource(PlayerResource Resource, int32 Quantity);
	void ReducePlayerResource(PlayerResource Resource, int32 Quantity);
	int32 GetResourcePossession(PlayerResource Resource) const;
	UTexture2D* GetResourceIcon(PlayerResource Resource) const;

	FSimpleEvent ResourcesUpdated;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere, Category="Settings")
	FPlayerData PlayerData;

	UPROPERTY(EditDefaultsOnly, Category="Resources");
	TMap<TEnumAsByte<PlayerResource>, UTexture2D*> Resources;

	
};
