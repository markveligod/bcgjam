// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BCGJamAIController.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API ABCGJamAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABCGJamAIController();

	UFUNCTION(BlueprintCallable)
		bool GetIsEnemy() const { return (this->bIsEnemy); }
	
protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UBCGJamAIPerceptionComponent* BCGJamPerceprtionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		float AIFieldOfView = 30.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		FName KeyEnemyBlackboard = "PlayerActor";
	
private:
	bool bIsEnemy = false;
};

