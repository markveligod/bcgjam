/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "CoreMinimal.h"
#include "HUD/UI/MSBJBaseWidget.h"
#include "MSBJMenuWidget.generated.h"

class UButton;
class UImage;
/**
 * 
 */
UCLASS()
class BCGJAM_API UMSBJMenuWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fon")
		TArray<UTexture2D*> ImagesArray;

	UPROPERTY(meta = (BindWidget))
		UImage* BackGround;
	
	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* EndAnimation;

	virtual void NativeOnInitialized() override;
private:
	class UMSBJGameInstance* GameInst;
	class AMenuSystemByJamGameModeBase* GameMode;
	
	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnOptionsGame();

	UFUNCTION()
		void OnCreditsGame();

	UFUNCTION()
		void OnQuitGame();
};
