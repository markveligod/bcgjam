/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#include "HUD/UI/MSBJCreditsWidget.h"
#include "Components/Button.h"
#include "Menu/MenuSystemByJamGameModeBase.h"
#include "Components/Image.h"
#include "Menu/Public/MSBJGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogMSBJCreditsWidget, All, All);

void UMSBJCreditsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	this->GameInst = Cast<UMSBJGameInstance>(GetWorld()->GetGameInstance());
	
	this->BackGround->SetBrushFromTexture(this->ImagesArray[FMath::RandRange(0, (this->ImagesArray.Num() - 1))]);
	this->BackGround->SetBrushSize(FVector2D(this->GameInst->GetScreenViewport().X, this->GameInst->GetScreenViewport().Y));

	
	this->BackButton->OnClicked.AddDynamic(this, &UMSBJCreditsWidget::OnComeBack);
}

void UMSBJCreditsWidget::OnComeBack()
{
	const auto GameMode = GetCurrentGameMode();
	if (!GameMode)
	{
		UE_LOG(LogMSBJCreditsWidget, Error, TEXT("Game mode is nullptr"));
		return;
	}
	GameMode->SetGameState(EMSBJGameMenuState::InProgress);
}
