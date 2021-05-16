// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/BCGJamAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Game/Public/AI/BCGJamAICharacter.h"
#include "Game/Public/AI/Components/BCGJamAIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ABCGJamAIController::ABCGJamAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	this->BCGJamPerceprtionComponent = CreateDefaultSubobject<UBCGJamAIPerceptionComponent>(TEXT("Perception Component"));
	SetPerceptionComponent(*this->BCGJamPerceprtionComponent);

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void ABCGJamAIController::BeginPlay()
{
	Super::BeginPlay();
	check(this->BCGJamPerceprtionComponent);
	check(GetBlackboardComponent());
	
}

void ABCGJamAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto TempEnemy = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(this->KeyEnemyBlackboard));
	SetFocus(TempEnemy);
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


