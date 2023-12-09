// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDisplay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UResourceDisplay::Setup(UTexture2D* NewIcon, int32 NewQuantity, PlayerResource Value) 
{
	Icon->SetBrushFromTexture(NewIcon,false);
	Quantity->SetText(FText::AsNumber(NewQuantity));
	Resource = Value;
}

void UResourceDisplay::Update(int32 NewQuantity) const
{
	Quantity->SetText(FText::AsNumber(NewQuantity));
}

PlayerResource UResourceDisplay::GetResource() const
{
	return Resource;
}
