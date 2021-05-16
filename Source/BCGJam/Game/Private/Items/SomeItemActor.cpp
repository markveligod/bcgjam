// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Items/SomeItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Game/Public/Character/BCGJamBaseCharacter.h"

// Sets default values
ASomeItemActor::ASomeItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	this->StaticMesh->SetupAttachment(GetRootComponent());

	this->BoxTrigger = CreateDefaultSubobject<UBoxComponent>("Box Component");
	this->BoxTrigger->SetupAttachment(this->StaticMesh);


}

// Called when the game starts or when spawned
void ASomeItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}


