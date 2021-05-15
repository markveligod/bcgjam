/*
 * By Mark Veligod
 * Company Name: VeligodStudio
 * GitHub: https://github.com/markveligod
 * Itch: https://veligodstudio.itch.io/
 * Contact: markveligod@yandex.ru
 */

#pragma once

#include "MSBJDataTypes.generated.h"

UENUM(BlueprintType)
enum class EMSBJGameMenuState : uint8
{
	WaitToStart = 0,
	WelcomeToGame,
    InProgress,
    Options,
    Credits
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameMenuStateChangedSignature, EMSBJGameMenuState);
DECLARE_MULTICAST_DELEGATE(FOnStartPlaySettingsSignature);

UENUM(BlueprintType)
enum class EGameLevelState : uint8
{
    WaitToStart = 0,
    InProgress,
    Pause
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameLevelStateChangedSignature, EGameLevelState);

