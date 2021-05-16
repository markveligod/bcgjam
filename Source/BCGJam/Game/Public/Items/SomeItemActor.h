// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SomeItemActor.generated.h"

UCLASS()
class BCGJAM_API ASomeItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASomeItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* BoxTrigger;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Param")
		int32 GoldValue = 50;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Param")
		bool IsKey = false;

private:
	bool bIsCharacterOverlap = false;
	class AGameJamModeBase* GameMode;

	void AddItemToArray(class ABCGJamBaseCharacter* TempCharacter);
	
	UFUNCTION()
		void OnCharacterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
