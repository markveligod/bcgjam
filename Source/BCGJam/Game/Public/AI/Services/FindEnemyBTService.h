// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindEnemyBTService.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API UFindEnemyBTService : public UBTService
{
	GENERATED_BODY()
public:
	UFindEnemyBTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
