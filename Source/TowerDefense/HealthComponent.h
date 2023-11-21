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

	UFUNCTION(BlueprintPure, BlueprintCallable )
	float GetHealthPercentage() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditDefaultsOnly, Category= "Health")
	float MaxHealth = 100;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* CausingDamageActor);

	UPROPERTY(VisibleAnywhere, Category="Health")
	float Health;

	bool bIsAlive;
};
