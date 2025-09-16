// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Moveing Platform"));
	Platform->SetupAttachment(RootComponent);

	SetActorScale3D(FVector(0.5f,0.5f,0.5f));

	MoveSpeed = 100;
	MaxRange = 500;

	Direaction = FVector(1.0f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	int Distance = FVector::Distance(CurrentLocation, StartLocation);

	AddActorLocalOffset(Direaction * DeltaTime * MoveSpeed);

	if (Distance > MaxRange)
	{
		SetActorLocation(StartLocation + Direaction * MaxRange);

		Direaction *= -1;
	}
}

