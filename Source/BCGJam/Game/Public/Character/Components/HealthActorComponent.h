// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthActorComponent.generated.h"


class AGameJamModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BCGJAM_API UHealthActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthActorComponent();

	UFUNCTION(BlueprintCallable)
	int32 GetHealthValue() const { return (this->HealthValue); }

	bool GetIsDead() const { return (this->IsDead); }
	void DecreaseHealthValue();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	AGameJamModeBase* GameMode;
	
	int32 HealthValue = 3;
	bool IsDead = false;

		
};
