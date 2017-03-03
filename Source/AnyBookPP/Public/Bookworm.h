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
	UFUNCTION(BlueprintCallable)
	void NextPage();
	UFUNCTION(BlueprintCallable)
	void PrevPage();
	void ToggleLayBookAside();
	void ToggleChangeBook();
	void LoadFile();

	UFUNCTION(BlueprintCallable)
		virtual void OnReceiveUpdate0(class UCanvas* Canvas, int32 Width, int32 Height);
	UFUNCTION(BlueprintCallable)
		virtual void OnReceiveUpdate1(class UCanvas* Canvas, int32 Width, int32 Height);
	UFUNCTION(BlueprintCallable)
		virtual void OnReceiveUpdate2(class UCanvas* Canvas, int32 Width, int32 Height);
	UFUNCTION(BlueprintCallable)
		virtual void OnReceiveUpdate3(class UCanvas* Canvas, int32 Width, int32 Height);

	///////////////////////////////////
	// Params...
	///////////////////////////////////
	
	bool bBookLayedAside;
	bool bBookChange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Book)
	USkeletalMeshComponent* BookSKMComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Book)
	USkeletalMeshComponent* Cover;

	

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Pages)
	UTexture* PageTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pages)
	TArray< int32 > Pages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pages)
	TArray< class UCanvasRenderTarget2D* > Canvs;
	
	int32 CanvasWidth;
	int32 CanvasHeight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Pages)
	FName ParamName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pages)
	TArray< UMaterialInstanceDynamic* > DMIs;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Pages)
	UMaterial* TextureMaterial;
	
	UTextureRenderTarget2D* TextureRT2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pages)
	UFont* CurrentFont;
	
	UAnimationAsset* ForwardAnim;
	UAnimationAsset* BackwardAnim;


	bool bLastTurnNext;
	bool bNewTurnNext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	TArray< FString > BookText;
	TArray< FString > CurrentTexts;

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