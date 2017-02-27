// Fill out your copyright notice in the Description page of Project Settings.

#include "AnyBookPP.h"
#include "Book.h"


ABook::ABook()
{
	PrimaryActorTick.bCanEverTick = true;
	
	/// Create objects...
	

	/// Set default parameters...
	CurrentPage = 0;
}
void ABook::BeginPlay()
{
	Super::BeginPlay();
	
}
void ABook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ABook::NextPage()
{
	if (++CurrentPage > Header.PageCount)
	{
		--CurrentPage;
		return false;
	}
	else
	{
		ShowText();
		return true;
	}
}
bool ABook::PrevPage()
{
	if (--CurrentPage < 0)
	{
		++CurrentPage;
		return false;
	}
	else
	{
		ShowText();
		return true;
	}
}
bool ABook::TurnToPage(int32 NewPage)
{
	if (NewPage <= Header.PageCount)
	{
		CurrentPage = NewPage;
		ShowText();
		return true;
	}
	else
	{
		return false;
	}
}

void ABook::ShowText()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Update Text"));
}