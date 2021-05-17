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
#include "MSBJCreditsWidget.generated.h"

class UButton;
class UImage;
/**
 * 
 */
UCLASS()
class BCGJAM_API UMSBJCreditsWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fon")
		TArray<UTexture2D*> ImagesArray;

	UPROPERTY(meta = (BindWidget))
		UImage* BackGround;
	
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	virtual void NativeOnInitialized() override;

private:
	class UMSBJGameInstance* GameInst;
	UFUNCTION()
		void OnComeBack();
};
