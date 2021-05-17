// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Character/Components/HealthActorComponent.h"
#include "Game/Public/GameJamModeBase.h"
#include "Game/Public/Character/BCGJamBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
UHealthActorComponent::UHealthActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UHealthActorComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(GetWorld(), TEXT("World is nullptr"));
	this->GameMode = Cast<AGameJamModeBase>(GetWorld()->GetAuthGameMode());
	this->Character = Cast<ABCGJamBaseCharacter>(GetOwner());
	checkf(this->GameMode, TEXT("Game mode is nullptr"));
	checkf(this->Character, TEXT("Character is nullptr"))
	
}

void UHealthActorComponent::DecreaseHealthValue()
{
	if (this->HealthValue == 0)
		return;
	
	this->HealthValue--;
	UE_LOG(LogHealthComponent, Display, TEXT("Health is %d"), this->HealthValue);
	if (this->HealthValue == 0)
	{
		UE_LOG(LogHealthComponent, Display, TEXT("Player is Dead"));
		this->IsDead = true;
		this->Character->PlayAnimMontage(this->DeathPlayer);
		this->GameMode->OnGameOver.Broadcast();
	}
}


