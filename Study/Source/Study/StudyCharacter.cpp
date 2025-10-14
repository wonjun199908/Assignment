// Copyright Epic Games, Inc. All Rights Reserved.

#include "StudyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "StudyPlayerController.h"
#include "StudyGameState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AStudyCharacter



AStudyCharacter::AStudyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	DefaultSpeed = GetCharacterMovement()->MaxWalkSpeed;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	OverHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidget"));
	OverHeadWidget->SetupAttachment(GetMesh());
	OverHeadWidget->SetWidgetSpace(EWidgetSpace::Screen);

	MaxHealth = 100.f;
	Health = MaxHealth;

	bIsReverseController = false;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStudyCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AStudyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping

		AStudyPlayerController* PlayerController = Cast<AStudyPlayerController>(GetController());

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStudyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStudyCharacter::Look);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AStudyCharacter::Pause);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AStudyCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		//const FVector ForwardDirection = FollowCamera->GetForwardVector()

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// add movement 

		int Reverse;

		Reverse = bIsReverseController ? -1 : 1;

		AddMovementInput(ForwardDirection, MovementVector.Y * Reverse);
		AddMovementInput(RightDirection, MovementVector.X * Reverse);
	}
}

void AStudyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AStudyCharacter::Pause(const FInputActionValue& Value)
{
	if (AStudyPlayerController* PlayerController = Cast<AStudyPlayerController>(Controller))
	{
		PlayerController->ShowPauseMenu(false);
	}
}

void AStudyCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateOverHeadHP();

}

void AStudyCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.f, MaxHealth);
	UpdateOverHeadHP();
}




float AStudyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - ActualDamage, 0.f, MaxHealth);
	UpdateOverHeadHP();

	if (Health <= 0.f)
	{
		OnDeath();
	}
	

	return ActualDamage;
}

void AStudyCharacter::OnDeath()
{
	if (AStudyGameState* GameState = Cast<AStudyGameState>(GetWorld()->GetGameState()))
	{
		GameState->OnGameOver();
	}
}

void AStudyCharacter::UpdateOverHeadHP()
{
	if (!OverHeadWidget) return;

	UUserWidget* OverHeadWidgetInstance = OverHeadWidget->GetUserWidgetObject();
	if (!OverHeadWidgetInstance) return;

	/*if (UTextBlock* HPText = Cast<UTextBlock>(OverHeadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
	{
		HPText->SetText(FText::FromString(FString::Printf(TEXT("%f / %f"), Health, MaxHealth)));
	}*/

	if (UProgressBar* Bar = Cast<UProgressBar>(OverHeadWidgetInstance->GetWidgetFromName("HPBar")))
	{
		Bar->SetPercent(Health / MaxHealth);
	}
}

void AStudyCharacter::ActiveDebuff(const EDebuffType& DebuffType)
{
	switch (DebuffType)
	{
		case EDebuffType::Slow:
			GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed * 0.5;

			GetWorldTimerManager().SetTimer(SlowDebuffTimerHandle, this, &AStudyCharacter::DeactiveSlowDebuff, 5.f);
			ActiveDebuffs.Add(EDebuffType::Slow, SlowDebuffTimerHandle);
			break;
		case EDebuffType::ReverseController:
			bIsReverseController = true;
			GetWorldTimerManager().SetTimer(ReverseDebuffTimerHandle, this, &AStudyCharacter::DeactiveReverseDebuff, 5.f);
			ActiveDebuffs.Add(EDebuffType::ReverseController, ReverseDebuffTimerHandle);
			break;
		case EDebuffType::Blind:
			if (AStudyPlayerController* PlayerController = Cast<AStudyPlayerController>(Controller))
			{
				PlayerController->BlindAnim();

				UE_LOG(LogTemp, Error, TEXT("player"));
			}
			GetWorldTimerManager().SetTimer(BlindDebuffTimerHandle, this, &AStudyCharacter::DeactiveBlindDebuff, 5.f);
			ActiveDebuffs.Add(EDebuffType::Blind, BlindDebuffTimerHandle);
			break;
	}

}

//void AStudyCharacter::ActiveSlowDebuff()
//{
//	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed * 0.5;
//
//	FTimerHandle SlowDebuffTimerHandle;
//
//	GetWorldTimerManager().SetTimer(SlowDebuffTimerHandle, this, &AStudyCharacter::DeactiveSlowDebuff, 5.f);
//	
//}
//
void AStudyCharacter::DeactiveSlowDebuff()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;

	ActiveDebuffs.Remove(EDebuffType::Slow);
}

void AStudyCharacter::DeactiveReverseDebuff()
{
	bIsReverseController = false;

	ActiveDebuffs.Remove(EDebuffType::ReverseController);
}

void AStudyCharacter::DeactiveBlindDebuff()
{
	ActiveDebuffs.Remove(EDebuffType::Blind);
}
