// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerPawn.generated.h"

class UCameraComponent;
class UMovementComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class TOWERDEFENSE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* HoverAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ZoomInOutAction;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float HoverSpeed = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float ZoomInOutSpeed = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D HoverMargins = FVector2D(200, 200);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MaxZoomIn = 300;

private:
	void Hover(const FInputActionValue& value);
	void ZoomInOut(const FInputActionValue& value);

	FVector OriginalLocation;
	class ABuildingTerrainTile* HighligtedBuildingTile;
	APlayerController* PlayerController;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
