// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/Services/FindEnemyBTService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/Public/AI/Components/BCGJamAIPerceptionComponent.h"

UFindEnemyBTService::UFindEnemyBTService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Controller->FindComponentByClass<UBCGJamAIPerceptionComponent>();
        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(this->EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClossesEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}



