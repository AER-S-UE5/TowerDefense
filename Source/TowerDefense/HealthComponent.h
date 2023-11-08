// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	void DecreaseHealth(float Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditDefaultsOnly, Category= "Health")
	float MaxHealth = 100;

	float Health;

	bool bIsAlive;
};
