// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatePlatform.generated.h"

UCLASS()
class ASSIGNMENT06_API ARotatePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatePlatform();
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Platform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	int RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FRotator Direaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	int StartTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	

};
