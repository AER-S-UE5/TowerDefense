// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/MovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Terrain/BuildingTerrainTile.h"

void APlayerPawn::Hover(const FInputActionValue& value)
{
	FVector DeltaMovement = value.Get<FVector>();
	DeltaMovement *= HoverSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector NewLocation = GetActorLocation() + DeltaMovement;
	NewLocation.X = FMath::Clamp(NewLocation.X, OriginalLocation.X - HoverMargins.X, OriginalLocation.X + HoverMargins.X);
	NewLocation.Y = FMath::Clamp(NewLocation.Y, OriginalLocation.Y - HoverMargins.Y, OriginalLocation.Y + HoverMargins.Y);
	SetActorLocation(NewLocation);

}

void APlayerPawn::ZoomInOut(const FInputActionValue& value)
{
	float DeltaMovement = value.Get<float>();
	FVector NewZoom = GetActorLocation() + GetActorForwardVector() * DeltaMovement * ZoomInOutSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	float NewZoomDistance = FVector::Distance(OriginalLocation, NewZoom);
	if (NewZoomDistance > 0 && NewZoomDistance < MaxZoomIn)
	{
		AddActorLocalOffset(FVector::ForwardVector * DeltaMovement * ZoomInOutSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
	}
}

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	RootComponent = CameraComponent;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultInputMappingContext, 0);
		}
	}

	OriginalLocation = GetActorLocation();
}


void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerController != nullptr)
	{
		
		FHitResult HitResult;
		if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			
			ABuildingTerrainTile* HitActor = Cast<ABuildingTerrainTile>(HitResult.GetActor());
			if (HitActor)
			{
				if (HitActor == HighligtedBuildingTile) return;
				if(HighligtedBuildingTile) HighligtedBuildingTile->OutlineTile(false);
				HighligtedBuildingTile = HitActor;
				HighligtedBuildingTile->OutlineTile(true);
			}
			else
			{
				if(HighligtedBuildingTile) HighligtedBuildingTile->OutlineTile(false);
				HighligtedBuildingTile = nullptr;
			}
		}
	}
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedPlayerComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedPlayerComponent->BindAction(HoverAction, ETriggerEvent::Triggered, this, &APlayerPawn::Hover);
		EnhancedPlayerComponent->BindAction(ZoomInOutAction, ETriggerEvent::Triggered, this, &APlayerPawn::ZoomInOut);
	}

}

