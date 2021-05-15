// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BCGJamAICharacter.generated.h"

UCLASS()
class BCGJAM_API ABCGJamAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABCGJamAICharacter();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BTreeAICharacter;

	FVector NextTargetPointLocation();
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Target")
	TArray<class ABCGJamAITargetPoint*> GeneralTargetPoints;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 CurrentPoint = 0;
	bool IsRevers = false;
};



