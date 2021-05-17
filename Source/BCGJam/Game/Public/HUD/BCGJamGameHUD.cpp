// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/HUD/BCGJamGameHUD.h"
#include "Game/Public/GameJamModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogJamGameHUD, All, All);

void ABCGJamGameHUD::BeginPlay()
{
	Super::BeginPlay();
	check(GetWorld());

	this->GameWidgets.Add(EGameLevelState::InProgress, CreateWidget<UUserWidget>(GetWorld(), this->GameHudWidgetClass));
	this->GameWidgets.Add(EGameLevelState::GameOver, CreateWidget<UUserWidget>(GetWorld(), this->GameOverHudWidgetClass));
	this->GameWidgets.Add(EGameLevelState::Pause, CreateWidget<UUserWidget>(GetWorld(), this->PauseHudWidgetClass));
	this->GameWidgets.Add(EGameLevelState::Map, CreateWidget<UUserWidget>(GetWorld(), this->MapHudWidgetClass));
	
	for (auto Widget : this->GameWidgets)
	{
		const auto ValueWidget = Widget.Value;
		ValueWidget->AddToViewport();
		ValueWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	this->GameMode = Cast<AGameJamModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	checkf(GameMode, TEXT("Game Mode is nullptr"));
	this->GameMode->GameLevelState.AddUObject(this, &ABCGJamGameHUD::OnGameStateChanged);
}

void ABCGJamGameHUD::OnGameStateChanged(EGameLevelState NewState)
{
	if (this->CurrentWidget)
	{
		this->CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (this->GameWidgets.Contains(NewState))
	{
		this->CurrentWidget = this->GameWidgets[NewState];
	}
	if (this->CurrentWidget)
	{
		this->CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	UE_LOG(LogJamGameHUD, Display, TEXT("New State: %s"), *UEnum::GetValueAsString(NewState))
}
