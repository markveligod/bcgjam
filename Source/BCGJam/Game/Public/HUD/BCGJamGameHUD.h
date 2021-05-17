// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Menu/Public/MSBJDataTypes.h"
#include "BCGJamGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API ABCGJamGameHUD : public AHUD
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PauseHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverHudWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> MapHudWidgetClass;

	virtual void BeginPlay() override;
private:
	class AGameJamModeBase* GameMode;
	UPROPERTY()
		TMap<EGameLevelState, UUserWidget*> GameWidgets;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;

	void OnGameStateChanged(EGameLevelState NewState);
};
