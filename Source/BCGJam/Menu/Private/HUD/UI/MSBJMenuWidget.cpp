/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "HUD/UI/MSBJMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Menu/MenuSystemByJamGameModeBase.h"
#include "Menu/Public/MSBJGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Image.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJMenuWidget, All, All);

void UMSBJMenuWidget::NativeOnInitialized()
{
	
	this->GameMode = GetCurrentGameMode();
	this->GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	
	this->BackGround->SetBrushFromTexture(this->ImagesArray[FMath::RandRange(0, (this->ImagesArray.Num() - 1))]);
	this->BackGround->SetBrushSize(FVector2D(this->GameInst->GetScreenViewport().X, this->GameInst->GetScreenViewport().Y));

	this->StartGameButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnStartGame);
	this->OptionsButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnOptionsGame);
	this->CreditsButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnCreditsGame);
	this->QuitButton->OnClicked.AddDynamic(this, &UMSBJMenuWidget::OnQuitGame);
}

void UMSBJMenuWidget::OnStartGame()
{
	if (!GetWorld())
		return;
	PlayAnimation(this->EndAnimation);
	UGameplayStatics::OpenLevel(GetWorld(), this->GameInst->NameStartLevel);
}

void UMSBJMenuWidget::OnOptionsGame()
{
	this->GameMode->SetGameState(EMSBJGameMenuState::Options);
}

void UMSBJMenuWidget::OnCreditsGame()
{
	this->GameMode->SetGameState(EMSBJGameMenuState::Credits);
}

void UMSBJMenuWidget::OnQuitGame()
{
	PlayAnimation(this->EndAnimation);
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
