// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageActorComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BCGJAM_API UDamageActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Param Editor")
		class UBoxComponent* BoxComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Param Editor")
		float ImpulseForce = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Param Editor")
		int32 DamageCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim")
		class UAnimMontage* AttackAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim")
		float InRateAnimAttack = 1.f;


private:
	class ABCGJamAICharacter* AICharacter;
	class ABCGJamBaseCharacter* TempCharacter;
	class UHealthActorComponent* HealthComp;
	FTimerHandle TimerHandleAttack;

	void TryAttackToCharacter();
	
	UFUNCTION()
		void OnDamageImpulse(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
		
};
