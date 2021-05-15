// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "BCGJamAITargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API ABCGJamAITargetPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	FVector GetLocationTargetPoint() const { return (this->LocationTargetPoint); }

protected:
	virtual void BeginPlay() override;

private:
	FVector LocationTargetPoint;
};
