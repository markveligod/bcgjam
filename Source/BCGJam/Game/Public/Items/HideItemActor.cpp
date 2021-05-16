// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Items/HideItemActor.h"
#include "Game/Public/Character/BCGJamBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHideItemActor, All, All);

// Sets default values
AHideItemActor::AHideItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	this->StaticMesh->SetupAttachment(GetRootComponent());

	this->BoxTrigger = CreateDefaultSubobject<UBoxComponent>("Box Component");
	this->BoxTrigger->SetupAttachment(this->StaticMesh);

	this->BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AHideItemActor::CharacterIsAround);
	this->BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AHideItemActor::CharacterIsNotAround);
}

// Called when the game starts or when spawned
void AHideItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHideItemActor::CharacterIsAround(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ABCGJamBaseCharacter::StaticClass()))
	{
		UE_LOG(LogHideItemActor, Display, TEXT("Actor %s is begin overlap hidden"), *OtherActor->GetName());
		const auto TempCharacter = Cast<ABCGJamBaseCharacter>(OtherActor);
		TempCharacter->SetHiddenItemAround(true);
	}
}

void AHideItemActor::CharacterIsNotAround(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ABCGJamBaseCharacter::StaticClass()))
	{
		UE_LOG(LogHideItemActor, Display, TEXT("Actor %s is end overlap hidden"), *OtherActor->GetName());
		const auto TempCharacter = Cast<ABCGJamBaseCharacter>(OtherActor);
		TempCharacter->SetHiddenItemAround(false);
	}
}


