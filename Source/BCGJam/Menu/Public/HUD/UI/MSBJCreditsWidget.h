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
/**
 * 
 */
UCLASS()
class BCGJAM_API UMSBJCreditsWidget : public UMSBJBaseWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnComeBack();
};
