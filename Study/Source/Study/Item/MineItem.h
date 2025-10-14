// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
public:

	AMineItem();

	TObjectPtr<USphereComponent> ExplosionCollision;

	virtual void ActivateItem(AActor* Activator) override;
	void Explosion();

	UPROPERTY(EditAnywhere, Category = "Item|Effect")
	TObjectPtr<UParticleSystem> ExplosionParticle;
	UPROPERTY(EditAnywhere, Category = "Item|Effect")
	TObjectPtr<USoundBase> ExplosionSound;

	bool bHasExploded;


	UPROPERTY(EditAnywhere, Category = "Item")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, Category = "Item")
	float ExplosionRadius;

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 ExplosionDamage;
};
