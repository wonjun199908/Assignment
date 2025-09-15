// Fill out your copyright notice in the Description page of Project Settings.
#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
	StartLocation = FVector2D(0.f, 0.f);
	CurrentLoaction = StartLocation;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	int EvnetCount = 0;

	for (int i = 0; i < 10; i++)
	{
		Move();

		if (CreateEvent())
		{
			++EvnetCount;
		}
		
	}
	UE_LOG(LogTemp, Log, TEXT("(총 이동거리는 %f입니다.)"), Distance(StartLocation, CurrentLoaction));
	UE_LOG(LogTemp, Log, TEXT("(이벤트 실행 횟수는 총 %d회)"), EvnetCount);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector2D AMyActor::Step()
{
	FVector2D Move = FVector2D(FMath::RandRange(0, 1), FMath::RandRange(0, 1));

	return Move;

}

void AMyActor::Move()
{
	FVector2D BeforeLoaction = CurrentLoaction;
	CurrentLoaction += Step();

	UE_LOG(LogTemp, Log, TEXT("(%f, %f)"), CurrentLoaction.X, CurrentLoaction.Y);
	UE_LOG(LogTemp, Log, TEXT("(%f만큼 이동했습니다.)"), Distance(BeforeLoaction, CurrentLoaction));
}

float AMyActor::Distance(FVector2D beforelocation, FVector2D afterlocation)
{
	float x = afterlocation.X - beforelocation.X;
	float y = afterlocation.Y - beforelocation.Y;

	return sqrt(x * x + y * y);
}


bool AMyActor::CreateEvent()
{
	bool IsEvent = FMath::RandBool();

	if (IsEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("이벤트가 발생하였습니다."));
	}

	return IsEvent;
}