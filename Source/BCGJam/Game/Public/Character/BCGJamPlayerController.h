// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Menu/Public/MSBJDataTypes.h"
#include "BCGJamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API ABCGJamPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	class AGameJamModeBase* GameMode;
	void OnGameState(EGameLevelState GameState);
	void OnPauseGame();
};
