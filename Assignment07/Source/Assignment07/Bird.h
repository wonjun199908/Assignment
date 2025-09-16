// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class ASSIGNMENT07_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gravity")
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	bool bIsMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>  Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void MoveCancle(const FInputActionValue& Value);

	UFUNCTION()
	void Rotate(const FInputActionValue& Value);


	void Gravity(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Input")
	int MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	int GravitySpeed;

	
};
