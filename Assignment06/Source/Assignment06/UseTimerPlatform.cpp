// Fill out your copyright notice in the Description page of Project Settings.


#include "UseTimerPlatform.h"
#include "Components/BoxComponent.h"
#include "Assignment06Character.h"

// Sets default values
AUseTimerPlatform::AUseTimerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(RootComponent);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(Platform);
	Box->SetBoxExtent(FVector(240.f, 240.f, 30.f));

	Box->OnComponentBeginOverlap.AddDynamic(this, &AUseTimerPlatform::OnBeginOverlap);

	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));


}

// Called when the game starts or when spawned
void AUseTimerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}


void AUseTimerPlatform::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	FTimerHandle Timer1;
	FTimerHandle Timer2;

	if (AAssignment06Character* Character = Cast<AAssignment06Character>(OtherActor))
	{
		GetWorld()->GetTimerManager().SetTimer(Timer1,this, &AUseTimerPlatform::HiddenPlatform, 1.f, false);
		GetWorld()->GetTimerManager().SetTimer(Timer2, this, &AUseTimerPlatform::VisiblePlatform, 5.0f, false);
	}
	


}

void AUseTimerPlatform::HiddenPlatform()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AUseTimerPlatform::VisiblePlatform()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}


// Called every frame
void AUseTimerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



