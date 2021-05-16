// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/HealthActorComponent.h"
#include "GameFramework/Character.h"
#include "BCGJamBaseCharacter.generated.h"

UCLASS()
class BCGJAM_API ABCGJamBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABCGJamBaseCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetHiddenItemAround() const { return (this->bIsHideItemAround); }
	void SetHiddenItemAround(bool State) { this->bIsHideItemAround = State; }

	bool GetHiddenInItem() const { return (this->bIsHiddenPlayerInItem); }
	bool GetIsDead() const { return(this->HealthComponent->GetIsDead()); }

	TArray<AActor*> GetAllActorItems() const { return (this->ActorItems); }

	void SetSomeItem(bool State) { this->bIsSomeItem = State; }
	bool GetSomeItem() const { return (this->bIsSomeItem); }

	void AddNewItemToArray(AActor* NewItem) { this->ActorItems.Add(NewItem); }
	void AddCountGold(int32 Value) { this->GoldValue += Value; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UHealthActorComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Speed run editor")
		float MaxSpeedRun = 400.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 GoldValue = 0;
	
	AGameJamModeBase* GameMode;
	
	bool bIsSomeItem = false;
	
	TArray<AActor*> ActorItems;
	
	bool bIsHideItemAround = false;
	bool bIsHiddenPlayerInItem = false;
	
	float DefaultValueMaxVelocity;
	
	void OnMoveForward(float Amount);
	void OnMoveRight(float Amount);
	void OnHiddenPlayer();
	void OnPressMoveRunPlayer();
	void OnRealMoveRunPlayer();
	void OnRealTakeItem();
	
};
