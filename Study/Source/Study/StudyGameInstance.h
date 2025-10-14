// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StudyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UStudyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UStudyGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameData)
	int32 TotalScore;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = GameData)
	int32 CurrentLevelIndex;

	UFUNCTION(BlueprintCallable)
	void AddToScore(int32 Amount);

};
