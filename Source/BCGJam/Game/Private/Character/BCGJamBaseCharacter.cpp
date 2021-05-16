// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Character/BCGJamBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Game/Public/Character/Components/HealthActorComponent.h"

// Sets default values
ABCGJamBaseCharacter::ABCGJamBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	this->SpringArmComponent->SetupAttachment(GetRootComponent());

	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->CameraComponent->SetupAttachment(this->SpringArmComponent);

	this->HealthComponent = CreateDefaultSubobject<UHealthActorComponent>("Health Component");
}

// Called when the game starts or when spawned
void ABCGJamBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(this->SpringArmComponent, TEXT("Spring arm is nullptr"));
	checkf(this->CameraComponent, TEXT("Camera is nullptr"));
	checkf(this->HealthComponent, TEXT("Health Component is nullptr"));
}



// Called every frame
void ABCGJamBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABCGJamBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &ABCGJamBaseCharacter::OnMoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ABCGJamBaseCharacter::OnMoveRight);
	}
}

void ABCGJamBaseCharacter::OnMoveForward(float Amount)
{
	if (Amount == 0.0f)
		return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ABCGJamBaseCharacter::OnMoveRight(float Amount)
{
	if (Amount == 0.0f)
		return;
	AddMovementInput(GetActorRightVector(), Amount);
}