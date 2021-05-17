// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/Components/DamageActorComponent.h"
#include "Game/Public/Character/BCGJamBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Game/Public/Character/Components/HealthActorComponent.h"
#include "Game/Public/AI/BCGJamAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Game/Public/AI/BCGJamAICharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogDamageComponent, All, All);

// Sets default values for this component's properties
UDamageActorComponent::UDamageActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	this->BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Trigger");
	const auto TempAIParent = Cast<ABCGJamAICharacter>(GetOwner());
	if (TempAIParent)
		this->BoxComponent->SetupAttachment(TempAIParent->GetRootComponent());
	this->BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UDamageActorComponent::OnDamageImpulse);
}


// Called when the game starts
void UDamageActorComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(this->BoxComponent, TEXT("Box component is nullptr"));
	this->AICharacter = Cast<ABCGJamAICharacter>(GetOwner());
	checkf(this->AICharacter, TEXT("AICharacter is nullptr"));
}

void UDamageActorComponent::TryAttackToCharacter()
{
	if (HealthComp)
	{
		for (int32 i = 0; i < this->DamageCount; i++)
			HealthComp->DecreaseHealthValue();
		UE_LOG(LogDamageComponent, Display, TEXT("Vector Forward %s"), *GetOwner()->GetActorForwardVector().ToString());
		FVector TempForwardVector = GetOwner()->GetActorForwardVector();
		TempForwardVector.X *= this->ImpulseForce;
		TempForwardVector.Y *= this->ImpulseForce;
		TempForwardVector.Z += this->ImpulseForce;
		TempCharacter->GetCharacterMovement()->AddImpulse(TempForwardVector * 1000.f);
	}
	GetWorld()->GetTimerManager().ClearTimer(this->TimerHandleAttack);
}

void UDamageActorComponent::OnDamageImpulse(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ABCGJamBaseCharacter::StaticClass()))
	{
		
		UE_LOG(LogDamageComponent, Display, TEXT("Impulse actor overlap: %s"), *OtherActor->GetName());
		this->TempCharacter = Cast<ABCGJamBaseCharacter>(OtherActor);
		this->HealthComp = TempCharacter->FindComponentByClass<UHealthActorComponent>();
		if (this->TempCharacter && this->HealthComp && !this->TempCharacter->GetIsDead())
		{
			GetWorld()->GetTimerManager().SetTimer(this->TimerHandleAttack, this, &UDamageActorComponent::TryAttackToCharacter, this->InRateAnimAttack, false);
			this->AICharacter->PlayAnimMontage(this->AttackAnim);
		}
	}
}


