// Fill out your copyright notice in the Description page of Project Settings.

#include "AnyBookPP.h"
#include "Bookworm.h"
#include "CoreMisc.h"
#include "RenderUtils.h"
#include "Engine/CanvasRenderTarget2D.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"


ABookworm::ABookworm()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bBookLayedAside = false;
	bBookChange = false;
	bLastTurnNext = true;
	bNewTurnNext = false;
	Pages = {0, 1, 2, 3};

	CanvasWidth = CanvasHeight = 1024;
	ParamName = FName("TP2D");

	CurrentTexts.Init("", 4);

	BookText.Add(FString("1\t\t\t\t\t\t\t\tTODESFUGE\n"
	"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
	"Swarze Milch der Fru^he wir trinken sie abends\n"
	"wir trinken sie mittags und morgens\n wir trinken sie nachts\n"
	"wir trinken und trinken\n"
	"wir schaufeln ein Grab in den Lu^ften da liegt man nicht eng \n"
	"Ein Mann wohnt im Haus der spielt mit den Schlangen der schreibt\n"
	"der schreibt wenn es dunkelt nach Deutschland dein goldenes Haar Margarete\n"
	));
	BookText.Add(FString("Paul Celan\t\t\t\t\t\t\t\t\t2\n"
	"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
	"er schreibt es und tritt vor das Haus und es blitzen die Sterne er pfeift seine Ru^den herbei\n"
	"er pfeift seine Juden hervor la^sst schaufeln ein Grab in der Erde\n"
	"er befiehlt uns spielt auf nun zum Tanz\n"
	"Schwarze Milch der Frühe wir trinken dich nachts\n"
	"wir trinken dich morgens und mittags wir trinken dich abends\n"
	"wir trinken und trinken...\n"
	));


	BookText.Add(FString("3\t\t\t\t\t\tWe’ll Go No More A-Roving\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"So, we’ll go no more a - roving\n"
		"So late into the night,\n"
		"Though the heart be still as loving,\n"
		"And the moon be still as bright.\n"
		"For the sword outwears its sheath,\n"
		"And the soul wears out the breast,\n"
		"And the heart must pause to breathe,\n"
		"And love itself have rest.\n"
	));
	BookText.Add(FString("Lord Byron\t\t\t\t\t\t\t\t\t4\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"Though the night was made for loving,\n"
		"And the day returns too soon,\n"
		"Yet we’ll go no more a - roving\n"
		"By the light of the moon.\n"
	));


	BookText.Add(FString("1\t\t\t\t\t\t\t\tTODESFUGE\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"Swarze Milch der Fru^he wir trinken sie abends\n"
		"wir trinken sie mittags und morgens\n wir trinken sie nachts\n"
		"wir trinken und trinken\n"
		"wir schaufeln ein Grab in den Lu^ften da liegt man nicht eng \n"
		"Ein Mann wohnt im Haus der spielt mit den Schlangen der schreibt\n"
		"der schreibt wenn es dunkelt nach Deutschland dein goldenes Haar Margarete\n"
	));
	BookText.Add(FString("Paul Celan\t\t\t\t\t\t\t\t\t2\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"er schreibt es und tritt vor das Haus und es blitzen die Sterne er pfeift seine Ru^den herbei\n"
		"er pfeift seine Juden hervor la^sst schaufeln ein Grab in der Erde\n"
		"er befiehlt uns spielt auf nun zum Tanz\n"
		"Schwarze Milch der Frühe wir trinken dich nachts\n"
		"wir trinken dich morgens und mittags wir trinken dich abends\n"
		"wir trinken und trinken...\n"
	));


	BookText.Add(FString("1\t\t\t\t\t\t\t\tTODESFUGE\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"Swarze Milch der Fru^he wir trinken sie abends\n"
		"wir trinken sie mittags und morgens\n wir trinken sie nachts\n"
		"wir trinken und trinken\n"
		"wir schaufeln ein Grab in den Lu^ften da liegt man nicht eng \n"
		"Ein Mann wohnt im Haus der spielt mit den Schlangen der schreibt\n"
		"der schreibt wenn es dunkelt nach Deutschland dein goldenes Haar Margarete\n"
	));
	BookText.Add(FString("Paul Celan\t\t\t\t\t\t\t\t\t2\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"er schreibt es und tritt vor das Haus und es blitzen die Sterne er pfeift seine Ru^den herbei\n"
		"er pfeift seine Juden hervor la^sst schaufeln ein Grab in der Erde\n"
		"er befiehlt uns spielt auf nun zum Tanz\n"
		"Schwarze Milch der Frühe wir trinken dich nachts\n"
		"wir trinken dich morgens und mittags wir trinken dich abends\n"
		"wir trinken und trinken...\n"
	));


	BookText.Add(FString("1\t\t\t\t\t\t\t\tTODESFUGE\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"Swarze Milch der Fru^he wir trinken sie abends\n"
		"wir trinken sie mittags und morgens\n wir trinken sie nachts\n"
		"wir trinken und trinken\n"
		"wir schaufeln ein Grab in den Lu^ften da liegt man nicht eng \n"
		"Ein Mann wohnt im Haus der spielt mit den Schlangen der schreibt\n"
		"der schreibt wenn es dunkelt nach Deutschland dein goldenes Haar Margarete\n"
	));
	BookText.Add(FString("Paul Celan\t\t\t\t\t\t\t\t\t2\n"
		"\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n"
		"er schreibt es und tritt vor das Haus und es blitzen die Sterne er pfeift seine Ru^den herbei\n"
		"er pfeift seine Juden hervor la^sst schaufeln ein Grab in der Erde\n"
		"er befiehlt uns spielt auf nun zum Tanz\n"
		"Schwarze Milch der Frühe wir trinken dich nachts\n"
		"wir trinken dich morgens und mittags wir trinken dich abends\n"
		"wir trinken und trinken...\n"
	));




	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 0.f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	CameraComp->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->bUsePawnControlRotation = true;

	CurrentBook = CreateDefaultSubobject< ABook >(_T("Book"));
	CurrentBook->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	BookSKMComp = CreateDefaultSubobject< USkeletalMeshComponent >(_T("SKMComp"));
	BookSKMComp->GlobalAnimRateScale = 1.5;
	BookSKMComp->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	BookSKMComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	BookSKMComp->SetMobility(EComponentMobility::Movable);

	Cover = CreateDefaultSubobject< USkeletalMeshComponent >(_T("Cover"));
	Cover->GlobalAnimRateScale = 1.5;
	Cover->AttachToComponent(CameraComp, FAttachmentTransformRules::KeepRelativeTransform);
	Cover->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	Cover->SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UAnimSequence> anim(TEXT("AnimSequence'/Game/SKM/fw.fw'"));
	ForwardAnim = anim.Object;
	static ConstructorHelpers::FObjectFinder<UAnimSequence> r_anim(TEXT("AnimSequence'/Game/SKM/bw.bw'"));
	BackwardAnim = r_anim.Object;
}
void ABookworm::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	CurrentBook = GetWorld()->SpawnActor< ABook >(CurrentBook->StaticClass(), spawnParams);

	for (int i = 0; i < 4; ++i)
	{
		Canvs.Add(UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(GetWorld(), UCanvasRenderTarget2D::StaticClass()));
		
		if (TextureMaterial)
		DMIs.Add(UMaterialInstanceDynamic::Create(TextureMaterial, this));
	}

	Canvs[0]->OnCanvasRenderTargetUpdate.AddDynamic(this, &ABookworm::OnReceiveUpdate0);
	Canvs[1]->OnCanvasRenderTargetUpdate.AddDynamic(this, &ABookworm::OnReceiveUpdate1);
	Canvs[2]->OnCanvasRenderTargetUpdate.AddDynamic(this, &ABookworm::OnReceiveUpdate2);
	Canvs[3]->OnCanvasRenderTargetUpdate.AddDynamic(this, &ABookworm::OnReceiveUpdate3);
		
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
		for (int i = 0; i < 4; ++i)
		{
			Pages[i] += 2;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(Pages[i]));
		}
		bNewTurnNext = true;
	
		if (bLastTurnNext)
		{
			CurrentTexts[0] = CurrentTexts[2];
			CurrentTexts[1] = CurrentTexts[3];
		}
		else
		{
			
		}
		Canvs[2]->UpdateResource();
		Canvs[3]->UpdateResource();
		BookSKMComp->PlayAnimation(ForwardAnim, false);
		Canvs[0]->UpdateResource();
		Canvs[1]->UpdateResource();
		bLastTurnNext = true;
	}
	else
	{
	
	}
}
void ABookworm::PrevPage()
{
	if (CurrentBook->PrevPage())
	{
		bNewTurnNext = false;
		
		for (int i = 0; i < 4; ++i)
		{
			Pages[i] -= 2;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Pages[i]));

		}
		
		if (bLastTurnNext)
		{
		
		}
		else
		{
			CurrentTexts[2] = CurrentTexts[0];
			CurrentTexts[3] = CurrentTexts[1];
		}
		Canvs[0]->UpdateResource();
		Canvs[1]->UpdateResource();
		BookSKMComp->PlayAnimation(BackwardAnim, false);
		Canvs[2]->UpdateResource();
		Canvs[3]->UpdateResource();
		
		bLastTurnNext = false;
	}
	else
	{

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
	Cover->AddLocalRotation(DeltaRot);
	Cover->AddRelativeLocation(DeltaLoc);

	bBookLayedAside = !bBookLayedAside;
}
void ABookworm::ToggleChangeBook()
{
	UE_LOG(LogTemp, Warning, TEXT("Change Book"));
	if (bBookChange)
	{
	
	}
	else
	{
	
	}
	bBookChange = !bBookChange;
}
void ABookworm::LoadFile()
{
	FString filename = "C:\\Users\\WHS\\Documents\\Unreal Projects\\AnyBookPP\\AnyBookPP\\TestData\\Iron Feet";
	FFileHelper::LoadFileToString(BookText[0], *filename);
	//UE_LOG(LogTemp, Log, TEXT("LangFile: \n %s"), *BookText);
}


// Material...
void ABookworm::OnReceiveUpdate0(class UCanvas* Canvas, int32 Width, int32 Height)
{
	if (PageTexture)
	{
		Canvas->K2_DrawTexture(
			PageTexture,
			FVector2D(3.f, 3.f),
			FVector2D(Width, Height),
			FVector2D::ZeroVector
		);
	}
	
	if (!bLastTurnNext && bNewTurnNext)
	{
		//
	}
	else
	{
		if (bLastTurnNext && bNewTurnNext)
		{
			/// Done already...
			//TextToDisplay = BookText[Pages[2]];
		}
		else
		{
			CurrentTexts[0] = BookText[Pages[0]];
		}
	}
	
	if (CurrentFont)
	{
		Canvas->DrawText(
			CurrentFont,
			CurrentTexts[0],
			60.f, 60.f,
			1.f, 1.f
		);
	}
	Cover->SetMaterial(2, DMIs[0]); // TODO
	DMIs[0]->SetTextureParameterValue(ParamName, Canvs[0]);
}
void ABookworm::OnReceiveUpdate1(class UCanvas* Canvas, int32 Width, int32 Height)
{	
	if (!bLastTurnNext && bNewTurnNext)
	{
		//
	}
	else
	{
		if (bLastTurnNext && bNewTurnNext)
		{
			//CurrentTexts[1] = BookText[Pages[3]];
		}
		else
		{
			CurrentTexts[1] = BookText[Pages[1]];
		}
	}

	if (PageTexture)
	{
		Canvas->K2_DrawTexture(
			PageTexture,
			FVector2D(3.f, 3.f),
			FVector2D(Width, Height),
			FVector2D::ZeroVector
		);
	}
	if (CurrentFont)
	{
		Canvas->DrawText(
			CurrentFont,
			CurrentTexts[1],
			60.f, 60.f,
			1.f, 1.f
		);
	}
	
	BookSKMComp->SetMaterial(2, DMIs[1]); // TODO
	DMIs[1]->SetTextureParameterValue(ParamName, Canvs[1]);
}
void ABookworm::OnReceiveUpdate2(class UCanvas* Canvas, int32 Width, int32 Height)
{
	if (bLastTurnNext && !bNewTurnNext)
	{
		//
	}
	else
	{
		if (!bLastTurnNext && !bNewTurnNext)
		{
			//CurrentTexts[2] = BookText[Pages[0]];
		}
		else
		{
			CurrentTexts[2] = BookText[Pages[2]];
		}
	}

	if (PageTexture)
	{
		Canvas->K2_DrawTexture(
			PageTexture,
			FVector2D(3.f, 3.f),
			FVector2D(Width, Height),
			FVector2D::ZeroVector
		);
	}
	if (CurrentFont)
	{
		Canvas->DrawText(
			CurrentFont,
			CurrentTexts[2],
			60.f, 60.f,
			1.f, 1.f
		);
	}

	BookSKMComp->SetMaterial(1, DMIs[2]); // TODO
	DMIs[2]->SetTextureParameterValue(ParamName, Canvs[2]);
}
void ABookworm::OnReceiveUpdate3(class UCanvas* Canvas, int32 Width, int32 Height)
{
	if (bLastTurnNext && !bNewTurnNext)
	{
		//return;
	}
	else
	{
		if (!bLastTurnNext && !bNewTurnNext)
		{
			//CurrentTexts[3] = BookText[Pages[1]];
		}
		else
		{
			CurrentTexts[3] = BookText[Pages[3]];
		}
	}
	
	if (PageTexture)
	{
		Canvas->K2_DrawTexture(
			PageTexture,
			FVector2D(3.f, 3.f),
			FVector2D(Width, Height),
			FVector2D::ZeroVector
		);
	}
	if (CurrentFont)
	{
		Canvas->DrawText(
			CurrentFont,
			CurrentTexts[3],
			60.f, 60.f,
			1.f, 1.f
		);
	}
	
	Cover->SetMaterial(3, DMIs[3]); // TODO
	DMIs[3]->SetTextureParameterValue(ParamName, Canvs[3]);
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