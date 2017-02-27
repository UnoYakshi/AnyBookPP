// Fill out your copyright notice in the Description page of Project Settings.

#include "AnyBookPP.h"
#include "AnyBookPPGameModeBase.h"



void AAnyBookPPGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("\t -==- AnyBook -==-"));
	}
}