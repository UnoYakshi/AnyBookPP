// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Public/Book.h"
#include "Bookworm.generated.h"

UCLASS()
class ANYBOOKPP_API ABookworm : public APawn
{
	GENERATED_BODY()

public:
	ABookworm();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// Input...
	void ABookworm::PitchCamera(float AxisValue);
	void ABookworm::YawCamera(float AxisValue);
	void ABookworm::ZoomIn();
	void ABookworm::ZoomOut();

	// Book interface...
	void NextPage();
	void PrevPage();
	


	///////////////////////////////////
	// Params...
	///////////////////////////////////
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Book)
	USkeletalMeshComponent* BookSKMComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Book)
	USkeletalMesh* BookSMesh;
	UAnimationAsset* AnimToPlay;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Book)
	ABook* CurrentBook;

	UPROPERTY(EditAnywhere, Category = Book)
	TArray< ABook* > AvailableBooks;

	/// Input variables...
	float ZoomFactor;
	bool bZoomingIn;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
};