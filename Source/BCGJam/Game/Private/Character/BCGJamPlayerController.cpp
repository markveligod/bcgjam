// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Character/BCGJamPlayerController.h"
#include "Game/Public/GameJamModeBase.h"

void ABCGJamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GetWorld());
	this->GameMode = GetWorld()->GetAuthGameMode<AGameJamModeBase>();
	check(this->GameMode)

	this->GameMode->GameLevelState.AddUObject(this, &ABCGJamPlayerController::OnGameState);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void ABCGJamPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent)
		return;

	InputComponent->BindAction("Pause", IE_Pressed, this, &ABCGJamPlayerController::OnPauseGame);
}

void ABCGJamPlayerController::OnGameState(EGameLevelState GameState)
{
	if (GameState == EGameLevelState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
		this->GameMode->ClearPause();
	}
	else if (GameState == EGameLevelState::Pause)
	{
		this->GameMode->SetPause(this);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ABCGJamPlayerController::OnPauseGame()
{
	this->GameMode->ChangeGameLevelState(EGameLevelState::Pause);
}
