// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"


class UBoxComponent;
class ABaseItem;


UCLASS()
class STUDY_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> SpawningBox;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> ItemDataTable;

	UFUNCTION(BlueprintCallable)
	AActor* SpawnRandomItem();

	FItemSpawnRow* GetRandomItem() const;
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	FVector GetRandomPointInVolume() const;

};
