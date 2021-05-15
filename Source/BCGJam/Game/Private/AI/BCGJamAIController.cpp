// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/BCGJamAIController.h"
#include "Game/Public/AI/BCGJamAICharacter.h"

void ABCGJamAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABCGJamAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto TempCharacter = Cast<ABCGJamAICharacter>(InPawn);
	if (TempCharacter)
	{
		RunBehaviorTree(TempCharacter->BTreeAICharacter);
	}
}
