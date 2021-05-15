// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/Tasks/NextLocationBTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/Public/AI/BCGJamAIController.h"
#include "Game/Public/AI/BCGJamAICharacter.h"

UNextLocationBTTaskNode::UNextLocationBTTaskNode()
{
	NodeName = "NextLocation";
}

EBTNodeResult::Type UNextLocationBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackbourd = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackbourd)
		return EBTNodeResult::Failed;
	
	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
		return EBTNodeResult::Failed;

	const auto CurrentCharacter = Cast<ABCGJamAICharacter>(Pawn);
	if (!CurrentCharacter)
		return EBTNodeResult::Failed;

	FVector NextLocationTarget = CurrentCharacter->NextTargetPointLocation();
	Blackbourd->SetValueAsVector(this->NewLocation.SelectedKeyName, NextLocationTarget);
	
	return EBTNodeResult::Succeeded;
}
