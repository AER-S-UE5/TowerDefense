// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTitleBar.h"

#include "Blueprint/WidgetTree.h"
#include "TowerDefense/TowerDefenseGameModeBase.h"
#include "ResourceDisplay.h"
#include "Components/HorizontalBox.h"
#include "TowerDefense/Components/PlayerResourcesManager.h"

void UGameTitleBar::SetGameMode(ATowerDefenseGameModeBase* value)
{
	GameMode = value;
}

void UGameTitleBar::Populate(TArray<TEnumAsByte<PlayerResource>> Resources)
{
	if(!Resources.IsEmpty())
	{
		for (auto Resource : Resources)
		{
			UResourceDisplay* ResourceDisplay = WidgetTree->ConstructWidget<UResourceDisplay>(ResourceDisplayClass);
			ResourceDisplay->Setup(GameMode->GetResourcesManager()->GetResourceIcon(Resource),GameMode->GetResourcesManager()->GetResourcePossession(Resource),Resource);
			ResourcesContainer->AddChildToHorizontalBox(ResourceDisplay);
		}
	}
	GameMode->GetResourcesManager()->ResourcesUpdated.AddDynamic(this, &UGameTitleBar::Update);
	
}

void UGameTitleBar::Update()
{
	for (const auto ResourceDisplay : ResourcesContainer->GetAllChildren())
	{
		if(const UResourceDisplay* Display =Cast<UResourceDisplay>(ResourceDisplay)) Display->Update(GameMode->GetResourcesManager()->GetResourcePossession(Display->GetResource()));
	}
}

void UGameTitleBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}
