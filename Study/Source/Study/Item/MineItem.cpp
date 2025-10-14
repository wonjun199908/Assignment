// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
AMineItem::AMineItem()
{
	ExplosionRadius = 300.f;
	ExplosionDelay = 5.f;
	ExplosionDamage = 30;

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetupAttachment(RootComponent);
	
	ItemType = "Mine";
	bHasExploded = false;
}

void AMineItem::ActivateItem(AActor* Activator)
{
	if (bHasExploded) return;

	Super::ActivateItem(Activator);

	FTimerHandle ExplosionTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AMineItem::Explosion, ExplosionDelay, false);

	bHasExploded = true;
}

void AMineItem::Explosion()
{
	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(),GetActorRotation(), true);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	TArray<AActor*> OverlappingActor;

	ExplosionCollision->GetOverlappingActors(OverlappingActor);

	for (AActor* Actor : OverlappingActor)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(Actor, ExplosionDamage,nullptr, this, UDamageType::StaticClass());
		}
	}

	DestroyItem();
}
