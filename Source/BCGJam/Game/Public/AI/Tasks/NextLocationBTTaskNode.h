// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocationBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class BCGJAM_API UNextLocationBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UNextLocationBTTaskNode();
	
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector NewLocation;
private:
	
};
