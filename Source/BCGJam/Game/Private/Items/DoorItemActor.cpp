// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Items/DoorItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Game/Public/Character/BCGJamBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogDoorItemActor, All, All);

// Sets default values
ADoorItemActor::ADoorItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	this->StaticMesh->SetupAttachment(GetRootComponent());

	this->BoxTrigger = CreateDefaultSubobject<UBoxComponent>("Box Component");
	this->BoxTrigger->SetupAttachment(this->StaticMesh);

	this->BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADoorItemActor::CharacterBeginOverlapDoor);
	this->BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ADoorItemActor::CharacterEndOverlapDoor);

}

// Called when the game starts or when spawned
void ADoorItemActor::BeginPlay()
{
	Super::BeginPlay();
	checkf(this->StaticMesh, TEXT("Static Mesh is nullptr"));
	checkf(this->BoxTrigger, TEXT("Box trigger is nullptr"));
}

void ADoorItemActor::CharacterBeginOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ABCGJamBaseCharacter::StaticClass()) && !this->bIsOpenDoor)
	{
		UE_LOG(LogDoorItemActor, Display, TEXT("Actor Begin overlap is %s"), *OtherActor->GetName());
		const auto TempCharacter = Cast<ABCGJamBaseCharacter>(OtherActor);
		if (TempCharacter)
		{
			const auto ArrayActorItems = TempCharacter->GetAllActorItems();
			for (auto Item : ArrayActorItems)
			{
				if (Item == this->Key)
				{
					UE_LOG(LogDoorItemActor, Display, TEXT("Key is done"));
					this->bIsOpenDoor = true;
					return;
				}
			}
			//TODO You need find to key
		}
	}
}

void ADoorItemActor::CharacterEndOverlapDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}



