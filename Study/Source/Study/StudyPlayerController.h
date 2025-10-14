// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StudyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API AStudyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AStudyPlayerController();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<UUserWidget> HUDWidgetClass;
	TObjectPtr<UUserWidget> HUDWidgetInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MenuWidgetClass;
	TObjectPtr<UUserWidget> MenuWidgetInstance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PauseWidgetClass;
	TObjectPtr<UUserWidget> PauseWidgetInstance;

	void ShowGameHUD();
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu(bool bIsRestart);
	void ShowPauseMenu(bool bIsEndlevel);
	UFUNCTION(BlueprintCallable)
	void RemovePauseMenu();

	UFUNCTION(BlueprintCallable)
	void OpenMenuLevel();

	void StartGame();

	UFUNCTION()
	void OnClickMainWidgetStartButton();
	UFUNCTION()
	void OnHoverMainWidgetStartButton();
	UFUNCTION()
	void OnUnHoverMainWidgetStartButton();
	UFUNCTION()
	void OnClickMainWidgetExitButton();
	UFUNCTION()
	void OnHoverMainWidgetExitButton();
	UFUNCTION()
	void OnUnHoverMainWidgetExitButton();

	UFUNCTION()
	void OnClickPauseWidgetNextButton();
	UFUNCTION()
	void OnClickPauseWidgetResumeButton();
	UFUNCTION()
	void OnHoverPauseWidgetResumeButton();
	UFUNCTION()
	void OnUnHoverPauseWidgetResumeButton();
	UFUNCTION()
	void OnClickPauseWidgetMenuButton();
	UFUNCTION()
	void OnHoverPauseWidgetMenuButton();
	UFUNCTION()
	void OnUnHoverPauseWidgetMenuButton();



	void OnHoverButton(UUserWidget* Widget, FName WidgetButtonName, FName WidgetButtonTextName) const;
	void OnUnHoverButton(UUserWidget* Widget, FName WidgetButtonName, FName WidgetButtonTextName) const;

	void UpdateDebuff();
	void BlindAnim();

	TObjectPtr<UTexture2D> SlowTexture;
	TObjectPtr<UTexture2D> ReverseTexture;
	TObjectPtr<UTexture2D> BlindTexture;

	FORCEINLINE UUserWidget* GetHUDWidget() const { return HUDWidgetInstance; }
	
};
