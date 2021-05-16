// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Menu/Public/MSBJDataTypes.h"
#include "GameJamModeBase.generated.h"

class UMSBJGameInstance;

/**
 * 
 */
UCLASS()
class BCGJAM_API AGameJamModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameJamModeBase();

	void ChangeGameLevelState(EGameLevelState NewState);
	FOnGameLevelStateChangedSignature GameLevelState;
	FOnGameOverSignature OnGameOver;
	
protected:
	virtual void StartPlay() override;
	
private:
	UMSBJGameInstance* GameInstance;
	UGameUserSettings* UserSettings;
	EGameLevelState CurrentGameLevelState = EGameLevelState::WaitToStart;
	
	void SetupSettings();
	void OnEndGame();
};
