// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorItemActor.generated.h"

UCLASS()
class BCGJAM_API ADoorItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorItemActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxTrigger;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Key")
		AActor* Key;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Key")
		FText DialogText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door")
		float DistTheDoor = 80.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door")
		float PowerTheDoor = 0.5f;
	UFUNCTION(BlueprintCallable)
		bool GetIsOpen() const { return (this->bIsOpen); }
private:
	bool bIsOpenDoor = false;
	bool bIsOpen = false;
	float StartLocalTheDoor;
	float TempLocalTheDoor;
	float EndLocalTheDoor;

	void StartOpenTheDoor(float Delta);
	
	UFUNCTION()
		void CharacterBeginOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CharacterEndOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

