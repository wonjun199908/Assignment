// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//#include "PlayerController.h"

// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = Sphere;
	Sphere->SetSimulatePhysics(false);
	Sphere->SetSphereRadius(15.f);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal"));
	SkeletalMesh->SetupAttachment(RootComponent);
	SkeletalMesh->SetSimulatePhysics(false);
	SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, -14.f));
	SkeletalMesh->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 100.f;
	SpringArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;


	MoveSpeed = 100;
	GravitySpeed = 100;
	bIsInAir = true;

}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (MappingContext)
			{
				SubSystem->AddMappingContext(MappingContext, 0);
			}
		}
	}


}

void ABird::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector MoveInput = Value.Get<FVector>();

	FVector Move = FVector(MoveInput.X, MoveInput.Y, MoveInput.Z) * MoveSpeed *  GetWorld()->GetDeltaSeconds();

	AddActorLocalOffset(Move, true);

	bIsMove = true;

}

void ABird::MoveCancle(const FInputActionValue& Value)
{
	bIsMove = false;
}

void ABird::Rotate(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector LookInput = Value.Get<FVector>();

	if (bIsInAir)
	{
		AddActorLocalRotation(FRotator(LookInput.Y, LookInput.X, LookInput.Z), true);
		return;
	}
	
	AddActorLocalRotation(FRotator(0.f, LookInput.X, LookInput.Z), true);

	SpringArm->AddLocalRotation(FRotator(LookInput.Y, 0.f, 0.f));

	FRotator SpringArmRotation = SpringArm->GetRelativeRotation();
	FRotator LimitPitch = FRotator(FMath::Clamp(SpringArmRotation.Pitch, -40, 40), SpringArmRotation.Yaw, SpringArmRotation.Roll);
	SpringArm->SetRelativeRotation(LimitPitch);
}

void ABird::Gravity(float DeltaTime)
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation - FVector(0.f, 0.f, 15.f);

	FHitResult HitResult;


	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 5.f);
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, TraceParams))
	{

		if (HitResult.GetActor())
		{
			bIsInAir = false;

			SetActorRotation(FRotator(0.f, GetActorRotation().Yaw, 0.f));

			return;
		}

	}

	if (!bIsMove)
	{
		FVector GravityVector = FVector(0.f, 0.f, -GravitySpeed * DeltaTime);

		AddActorWorldOffset(GravityVector);
	}

	bIsInAir = true;
}



// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Gravity(DeltaTime);
	
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABird::MoveCancle);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Rotate);
	}

}

