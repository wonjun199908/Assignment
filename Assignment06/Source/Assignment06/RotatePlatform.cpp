// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatePlatform.h"

// Sets default values
ARotatePlatform::ARotatePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

	Platform->SetRelativeLocation(FVector(0.f, 0.f, -300.f));



	RotationSpeed = 100;
	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
	Direaction = FRotator(0.f, 0.f, 1.f);

}

// Called when the game starts or when spawned
void ARotatePlatform::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void ARotatePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(Direaction * DeltaTime * RotationSpeed);

}

