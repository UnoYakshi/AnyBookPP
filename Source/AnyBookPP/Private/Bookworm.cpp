// Fill out your copyright notice in the Description page of Project Settings.

#include "AnyBookPP.h"
#include "Bookworm.h"


ABookworm::ABookworm()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//*
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 0.f;
	//*/

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	CameraComp->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->bUsePawnControlRotation = true;

	CurrentBook = CreateDefaultSubobject< ABook >(_T("Book"));
	BookSKMComp = CreateDefaultSubobject< USkeletalMeshComponent >(_T("SKMComp"));
	BookSKMComp->GlobalAnimRateScale = 1.5;
	BookSKMComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BookSKMComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

	//static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("AnimSequence'/Game/Mannequin/Animations/ThirdPersonJump_Start.ThirdPersonJump_Start'"));
	//AnimToPlay = anim.Object;
}
void ABookworm::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Bookworm's here!"));
	}
	if (BookSMesh)
	{
		BookSKMComp->SetSkeletalMesh(BookSMesh);
	}
}
void ABookworm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	//Zoom in if ZoomIn button is down, zoom back out if it's not
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		SpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}
	//*/
}


void ABookworm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up mouse input bindings...
	InputComponent->BindAxis("LookUp", this, &ABookworm::PitchCamera);
	InputComponent->BindAxis("TurnRight", this, &ABookworm::YawCamera);

	InputComponent->BindAction("NextPage", IE_Pressed, this, &ABookworm::NextPage);
	InputComponent->BindAction("PrevPage", IE_Pressed, this, &ABookworm::PrevPage);
}


// Book interface...
void ABookworm::NextPage()
{
	if (CurrentBook->NextPage())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Next :: true"));
		//BookSKMComp->PlayAnimation(AnimToPlay, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Next :: false"));
	}
}
void ABookworm::PrevPage()
{
	if (CurrentBook->PrevPage())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Prev :: True"));
	
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Prev :: false"));

	}
}


//Input functions
void ABookworm::PitchCamera(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}
void ABookworm::YawCamera(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ABookworm::ZoomIn()
{
	bZoomingIn = true;
}
void ABookworm::ZoomOut()
{
	bZoomingIn = false;
}