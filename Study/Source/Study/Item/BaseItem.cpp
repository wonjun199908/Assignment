// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
ABaseItem::ABaseItem()
{
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	
	Collison = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Collison->SetupAttachment(RootComponent);

	Collison->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collison->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collison);
	
	
}


void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("overlap")));

		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ABaseItem::ActivateItem(AActor* Activator)
{
	UParticleSystemComponent* Particle = nullptr;

	if (PickupParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupParticle, GetActorLocation(), GetActorRotation(), true);
	}
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	}

	if (Particle)
	{
		FTimerHandle DestroyParticleTimerHandl;

		TWeakObjectPtr<UParticleSystemComponent> WeakParticle = Particle;

		GetWorldTimerManager().SetTimer(DestroyParticleTimerHandl,
			[WeakParticle]()
			{
				
				if (WeakParticle.IsValid())
				{
					WeakParticle->DestroyComponent();
				}
							
			},
			2.0f,
			false
		);
	}

}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
}





