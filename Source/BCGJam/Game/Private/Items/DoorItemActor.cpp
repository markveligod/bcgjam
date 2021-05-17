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
	PrimaryActorTick.bCanEverTick = true;

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

	this->StartLocalTheDoor = this->StaticMesh->GetComponentRotation().Yaw;
	this->EndLocalTheDoor = this->StartLocalTheDoor + this->DistTheDoor;
	this->TempLocalTheDoor = this->StartLocalTheDoor;

}

void ADoorItemActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (this->bIsOpenDoor)
	{
		this->StartOpenTheDoor(DeltaSeconds);
	}
}

void ADoorItemActor::StartOpenTheDoor(float Delta)
{
	FRotator TempVectorLocalTheDoor = this->StaticMesh->GetComponentRotation();
	this->TempLocalTheDoor = FMath::Lerp(this->TempLocalTheDoor, this->EndLocalTheDoor, Delta * this->PowerTheDoor);
	TempVectorLocalTheDoor.Yaw = this->TempLocalTheDoor;
	this->StaticMesh->SetRelativeRotation(TempVectorLocalTheDoor);
	if (this->TempLocalTheDoor + 2.f >= this->EndLocalTheDoor)
		this->bIsOpenDoor = false;
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
			UE_LOG(LogDoorItemActor, Display, TEXT("Array Item count %d"), ArrayActorItems.Num());
			for (auto Item : ArrayActorItems)
			{
				if (Item == this->Key)
				{
					UE_LOG(LogDoorItemActor, Display, TEXT("Key is done"));
					this->bIsOpenDoor = true;
					this->BoxTrigger->OnComponentBeginOverlap.Clear();
					this->BoxTrigger->OnComponentEndOverlap.Clear();
					this->bIsOpen = true;
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



