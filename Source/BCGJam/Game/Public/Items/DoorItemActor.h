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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxTrigger;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Key")
		AActor* Key;
	
	
private:
	bool bIsOpenDoor = false;
	
	UFUNCTION()
		void CharacterBeginOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void CharacterEndOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
