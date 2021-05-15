// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "BCGJamAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API UBCGJamAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	AActor* GetClossesEnemy();
	
protected:

private:
	
};
