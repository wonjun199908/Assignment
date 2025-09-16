// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"


class UStaticMeshComponent;

UCLASS()
class ASSIGNMENT06_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMovingPlatform();
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> Platform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	int MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	int MaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
	FVector Direaction;

	FVector StartLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	

};
