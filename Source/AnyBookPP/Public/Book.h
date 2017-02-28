// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Book.generated.h"

USTRUCT()
struct FBookHeader 
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PageCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PageWidth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PageHeight;

	FBookHeader() :
	Title("default_title"),
	PageCount(100),
	PageWidth(60),
	PageHeight(40)
	{}
};

USTRUCT()
struct FTourNode
{
	GENERATED_USTRUCT_BODY()
};

UCLASS()
class ANYBOOKPP_API ABook : public AActor
{
	GENERATED_BODY()
	
public:
	ABook();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	/////////////////////////////////
	// Param-s...
	/////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Book)
	FBookHeader Header;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	int32 CurrentPage;
	

	/////////////////////////////////
	// Book functionality...
	bool NextPage();
	bool PrevPage();
	bool TurnToPage(int32 NewPage);
	void ShowText();

};
