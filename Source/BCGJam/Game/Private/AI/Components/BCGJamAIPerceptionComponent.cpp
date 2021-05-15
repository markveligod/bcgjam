// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/Components/BCGJamAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Game/Public/AI/BCGJamAIController.h"
#include "Game/Public/AI/BCGJamAICharacter.h"

AActor* UBCGJamAIPerceptionComponent::GetClossesEnemy()
{
	TArray<AActor*> AllActorSight;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), AllActorSight);
	if (AllActorSight.Num() == 0)
		return nullptr;
	const auto Controller = Cast<ABCGJamAIController>(GetOwner());
	if (!Controller)
		return (nullptr);

	const auto TempAICharacter = Cast<ABCGJamAICharacter>(Controller->GetPawn());
	if (!TempAICharacter)
		return (nullptr);

	AActor* ResultPawn = nullptr;
	for (auto TempActor : AllActorSight)
	{
		//TODO if actor is dead?
		//TODO check is player?
		ResultPawn = TempActor;
	}
	return (ResultPawn);
}
