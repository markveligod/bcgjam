// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/GameJamModeBase.h"
#include "Menu/Public/MSBJGameInstance.h"
#include "GameFramework/GameUserSettings.h"

AGameJamModeBase::AGameJamModeBase()
{
	
}

void AGameJamModeBase::ChangeGameLevelState(EGameLevelState NewState)
{
	if (this->CurrentGameLevelState == NewState)
		return;
	this->CurrentGameLevelState = NewState;
	this->GameLevelState.Broadcast(NewState);
}

void AGameJamModeBase::StartPlay()
{
	Super::StartPlay();

	checkf(GetWorld(), TEXT("World is nullptr"));
	this->GameInstance = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	checkf(this->GameInstance, TEXT("Game instance is nullptr"));
	this->UserSettings = UGameUserSettings::GetGameUserSettings();
	this->SetupSettings();

	this->ChangeGameLevelState(EGameLevelState::InProgress);
}

void AGameJamModeBase::SetupSettings()
{
	this->UserSettings->SetFullscreenMode(this->GameInstance->GetCurrentWindowMode());
	this->UserSettings->SetScreenResolution(this->GameInstance->GetScreenViewport());
	this->UserSettings->SetAntiAliasingQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetAudioQualityLevel(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetFoliageQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetPostProcessingQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetShadingQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetShadowQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetTextureQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetViewDistanceQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->SetVisualEffectQuality(this->GameInstance->GetCurrentQualityValue());
	this->UserSettings->ApplySettings(false);
}
