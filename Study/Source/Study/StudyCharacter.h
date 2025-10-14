// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Item/DebuffData.h"
#include "StudyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UWidgetComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AStudyCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> OverHeadWidget;

	UPROPERTY(EditAnywhere, Category = Health)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, Category = Health)
	float Health;

	void OnDeath();
	void UpdateOverHeadHP();
	
	bool bIsReverseController;

	float DefaultSpeed;

	TMap<EDebuffType, FTimerHandle> ActiveDebuffs;

	FTimerHandle SlowDebuffTimerHandle;
	FTimerHandle ReverseDebuffTimerHandle;
	FTimerHandle BlindDebuffTimerHandle;
public:
	AStudyCharacter();
	

protected:

	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Pause(const FInputActionValue& Value);

	virtual void BeginPlay() override;
			

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UFUNCTION(BlueprintCallable, Category = Health)
	void AddHealth(float Amount);


	void ActiveDebuff(const EDebuffType& DebuffType);
	//void ActiveSlowDebuff();
	void DeactiveSlowDebuff();
	void DeactiveReverseDebuff();
	void DeactiveBlindDebuff();

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealth() const { return Health; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class TMap<EDebuffType, FTimerHandle> GetActiveDebuffs() const { return ActiveDebuffs; }
	
};

