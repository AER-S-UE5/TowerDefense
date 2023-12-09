// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerResourcesManager.h"

// Sets default values for this component's properties
UPlayerResourcesManager::UPlayerResourcesManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerResourcesManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerResourcesManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerResourcesManager::AddPlayerResource(PlayerResource Resource, int32 Quantity) 
{
	int32 CurrentQuantity = 0;
	if(!PlayerData.Resources.IsEmpty() && PlayerData.Resources.Contains(Resource))
	{
		CurrentQuantity = PlayerData.Resources[Resource];
		UE_LOG(LogTemp,Warning,TEXT("Added Resource %d : %d"), Resource, Quantity);
	}

	PlayerData.Resources.Add(Resource, CurrentQuantity+Quantity);
}

void UPlayerResourcesManager::ReducePlayerResource(PlayerResource Resource, int32 Quantity) 
{
	if(!PlayerData.Resources.IsEmpty() && PlayerData.Resources.Contains(Resource))
	{
		const int32 NewQuantity = FMath::Max(PlayerData.Resources[Resource]-Quantity,0);
		PlayerData.Resources.Add(Resource, NewQuantity);
	}
}

int32 UPlayerResourcesManager::GetResourcePossession(PlayerResource Resource) const
{
	if(!PlayerData.Resources.IsEmpty() && PlayerData.Resources.Contains(Resource)) return PlayerData.Resources[Resource];
	return  0;
}

UTexture2D* UPlayerResourcesManager::GetResourceIcon(PlayerResource Resource) const
{
	if(!Resources.IsEmpty() && Resources.Contains(Resource))
	{
		return Resources[Resource];
	}
	return nullptr;
}
