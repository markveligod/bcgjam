// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/BCGJamAICharacter.h"
#include "Game/Public/AI/BCGJamAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Public/AI/BCGJamAITargetPoint.h"
#include "Game/Public/AI/Components/DamageActorComponent.h"

// Sets default values
ABCGJamAICharacter::ABCGJamAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ABCGJamAIController::StaticClass();

	this->DamageComponent = CreateDefaultSubobject<UDamageActorComponent>("Damage Component");
}

// Called when the game starts or when spawned
void ABCGJamAICharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(this->DamageComponent, TEXT("Damage component is nullptr"));
}

// Called to bind functionality to input
void ABCGJamAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ABCGJamAICharacter::NextTargetPointLocation()
{
	FVector ResultLocation;
	if (this->CurrentPoint == this->GeneralTargetPoints.Num())
		this->IsRevers = true;
	if (this->CurrentPoint == 0)
		this->IsRevers = false;

	if (this->IsRevers)
	{
		this->CurrentPoint--;
		ResultLocation = this->GeneralTargetPoints[this->CurrentPoint]->GetLocationTargetPoint();
	}
	else
	{
		ResultLocation = this->GeneralTargetPoints[this->CurrentPoint]->GetLocationTargetPoint();
		this->CurrentPoint++;
	}
	
	return (ResultLocation);
}

