// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Items/SomeItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Game/Public/Character/BCGJamBaseCharacter.h"
#include "Game/Public/GameJamModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogSomeItemActor, All, All);

// Sets default values
ASomeItemActor::ASomeItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	this->StaticMesh->SetupAttachment(GetRootComponent());

	this->BoxTrigger = CreateDefaultSubobject<UBoxComponent>("Box Component");
	this->BoxTrigger->SetupAttachment(this->StaticMesh);

	this->BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASomeItemActor::OnCharacterBeginOverlap);
	this->BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &ASomeItemActor::OnCharacterEndOverlap);
}

// Called when the game starts or when spawned
void ASomeItemActor::BeginPlay()
{
	Super::BeginPlay();

	checkf(this->StaticMesh, TEXT("Static Mesh is nullptr"));
	checkf(this->BoxTrigger, TEXT("Box trigger is nullptr"));
	checkf(GetWorld(), TEXT("World is nullptr"));
	this->GameMode = Cast<AGameJamModeBase>(GetWorld()->GetAuthGameMode());
	this->GameMode->OnTakeGameState.AddUObject(this, &ASomeItemActor::AddItemToArray);
}

void ASomeItemActor::AddItemToArray(ABCGJamBaseCharacter* TempCharacter)
{
	if (this->bIsCharacterOverlap)
	{
		if (this->IsKey)
			UGameplayStatics::PlaySound2D(GetWorld(), this->PlayFanFar);
		TempCharacter->AddCountGold(this->GoldValue);
		TempCharacter->AddNewItemToArray(this);
		TempCharacter->SetSomeItem(false);
		SetActorHiddenInGame(true);
		this->BoxTrigger->OnComponentBeginOverlap.Clear();
		this->BoxTrigger->OnComponentEndOverlap.Clear();
		this->bIsCharacterOverlap = false;
		auto TempLocation = GetActorLocation();
		TempLocation.Z -= 1000.f;
		SetActorLocation(TempLocation);
	}
}

void ASomeItemActor::OnCharacterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ABCGJamBaseCharacter::StaticClass()))
	{
		UE_LOG(LogSomeItemActor, Display, TEXT("Begin overlap actor is %s"), *OtherActor->GetName());
		this->bIsCharacterOverlap = true;
		const auto TempCharacter = Cast<ABCGJamBaseCharacter>(OtherActor);
		if (TempCharacter)
		{
			TempCharacter->SetSomeItem(true);
		}
	}
}

void ASomeItemActor::OnCharacterEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ABCGJamBaseCharacter::StaticClass()))
	{
		UE_LOG(LogSomeItemActor, Display, TEXT("End overlap actor is %s"), *OtherActor->GetName());
		this->bIsCharacterOverlap = false;
		const auto TempCharacter = Cast<ABCGJamBaseCharacter>(OtherActor);
		if (TempCharacter)
		{
			TempCharacter->SetSomeItem(false);
		}
	}
}


