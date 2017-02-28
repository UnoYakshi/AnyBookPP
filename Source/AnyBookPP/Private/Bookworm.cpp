// Fill out your copyright notice in the Description page of Project Settings.

#include "AnyBookPP.h"
#include "Bookworm.h"
#include "CoreMisc.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


ABookworm::ABookworm()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bBookLayedAside = false;


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
	CurrentBook->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	BookSKMComp = CreateDefaultSubobject< USkeletalMeshComponent >(_T("SKMComp"));
	BookSKMComp->GlobalAnimRateScale = 1.5;
	BookSKMComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BookSKMComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	BookSKMComp->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("AnimSequence'/Game/SKM/BookFroward_Anim.BookFroward_Anim'"));
	ForwardAnim = anim.Object;
	static ConstructorHelpers::FObjectFinder<UAnimSequence> r_anim(TEXT("AnimSequence'/Game/SKM/BookBackward_Anim.BookBackward_Anim'"));
	BackwardAnim = r_anim.Object;
}
void ABookworm::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Bookworm's here!"));
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	CurrentBook = GetWorld()->SpawnActor< ABook >(CurrentBook->StaticClass(), spawnParams);
	if (CurrentBook)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("SPAWNED"));
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
			ZoomFactor += DeltaTime / 0.5f;		//Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;		//Zoom out over a quarter of a second
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
	InputComponent->BindAction("ToggleLayBookAside", IE_Pressed, this, &ABookworm::ToggleLayBookAside);
	InputComponent->BindAction("LoadFile", IE_Pressed, this, &ABookworm::LoadFile);

}


// Book interface...
void ABookworm::NextPage()
{
	if (CurrentBook->NextPage())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Next :: true"));
		BookSKMComp->PlayAnimation(ForwardAnim, false);
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
		BookSKMComp->PlayAnimation(BackwardAnim, false);
		

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Prev :: false"));

	}
}
void ABookworm::ToggleLayBookAside()
{
	FRotator DeltaRot(0.f, 0.f, 40.f);
	FVector DeltaLoc(-120.f, 0.f, -160.f);
	
	/// TODO :: Make it with MoveComponentTo()...
	/*
	FRotator NewRot = BookSKMComp->GetComponentRotation() + DeltaRot;
	FVector NewLoc = BookSKMComp->GetComponentLocation() + DeltaLoc;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	//*/
	/*
	UKismetSystemLibrary::MoveComponentTo
	(
	BookSKMComp,
	NewLoc,
	NewRot,
	false,
	false,
	1.f,
	false,
	EMoveComponentAction::Type::Move,
	LatentInfo
	);
	//*/

	DeltaRot = (bBookLayedAside) ? -1.f * DeltaRot : DeltaRot;
	DeltaLoc = (bBookLayedAside) ? -1.f * DeltaLoc : DeltaLoc;

	BookSKMComp->AddLocalRotation(DeltaRot);
	BookSKMComp->AddRelativeLocation(DeltaLoc);

	bBookLayedAside = !bBookLayedAside;
}
void ABookworm::LoadFile()
{
	FString filename = "C:\\Users\\WHS\\Documents\\Unreal Projects\\AnyBookPP\\AnyBookPP\\TestData\\Iron Feet";
	FFileHelper::LoadFileToString(BookText, *filename);
	UE_LOG(LogTemp, Log, TEXT("LangFile: \n %s"), *BookText);
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