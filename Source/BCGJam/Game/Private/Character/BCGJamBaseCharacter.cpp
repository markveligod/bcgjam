// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/Character/BCGJamBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Game/Public/Character/Components/HealthActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/Public/GameJamModeBase.h"

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
	checkf(GetWorld(), TEXT("World is nullptr"));
	this->GameMode = Cast<AGameJamModeBase>(GetWorld()->GetAuthGameMode());
	checkf(this->GameMode, TEXT("Game mode is nullptr"));
	this->DefaultValueMaxVelocity = GetCharacterMovement()->GetMaxSpeed();

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
		PlayerInputComponent->BindAxis("MoveUp", this, &ABCGJamBaseCharacter::MoveUpPlayer);
		PlayerInputComponent->BindAxis("MoveRight", this, &ABCGJamBaseCharacter::MoveRightPlayer);
		PlayerInputComponent->BindAxis("MoveDown", this, &ABCGJamBaseCharacter::MoveDownPlayer);
		PlayerInputComponent->BindAxis("MoveLeft", this, &ABCGJamBaseCharacter::MoveLeftPlayer);

		PlayerInputComponent->BindAction("Hide", IE_Pressed, this, &ABCGJamBaseCharacter::OnHiddenPlayer);
		PlayerInputComponent->BindAction("MoveRun", IE_Pressed, this, &ABCGJamBaseCharacter::OnPressMoveRunPlayer);
		PlayerInputComponent->BindAction("MoveRun", IE_Released, this, &ABCGJamBaseCharacter::OnRealMoveRunPlayer);
		PlayerInputComponent->BindAction("TakeItem", IE_Released, this, &ABCGJamBaseCharacter::OnRealTakeItem);
	}
}

void ABCGJamBaseCharacter::OnHiddenPlayer()
{
	if (this->bIsHideItemAround && !this->bIsHiddenPlayerInItem)
	{
		this->bIsHiddenPlayerInItem = true;
		SetActorHiddenInGame(true);
	}
	else if (this->bIsHiddenPlayerInItem)
	{
		this->bIsHiddenPlayerInItem = false;
		SetActorHiddenInGame(false);
	}
}

void ABCGJamBaseCharacter::OnPressMoveRunPlayer()
{
	if (this->bIsHiddenPlayerInItem)
		return;
	this->bIsRun = true;
	GetCharacterMovement()->MaxWalkSpeed = this->MaxSpeedRun;
}

void ABCGJamBaseCharacter::OnRealMoveRunPlayer()
{
	if (this->bIsHiddenPlayerInItem)
		return;
	this->bIsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = this->DefaultValueMaxVelocity;
}

void ABCGJamBaseCharacter::OnRealTakeItem()
{
	if (!this->bIsSomeItem)
		return;
	PlayAnimMontage(this->TakeItemAnim);
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetTimerManager().SetTimer(this->TimerAnimationHandle, this, &ABCGJamBaseCharacter::ClearTimerAnim, this->InRateAnimTake, false);
}

void ABCGJamBaseCharacter::ClearTimerAnim()
{
	this->GameMode->OnTakeGameState.Broadcast(this);
	GetWorld()->GetTimerManager().ClearTimer(this->TimerAnimationHandle);
	EnableInput(GetWorld()->GetFirstPlayerController());
}

void ABCGJamBaseCharacter::MoveUpPlayer(float Amount)
{
	this->bIsMoveUp = Amount > 0.0f;
	if (Amount == 0.0f || this->bIsMoveDown || this->bIsMoveLeft || this->bIsMoveRight || this->bIsHiddenPlayerInItem)
		return;
	GetMesh()->SetRelativeRotation(this->ForwardMove);
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ABCGJamBaseCharacter::MoveRightPlayer(float Amount)
{
	this->bIsMoveRight = Amount > 0.0f;
	if (Amount == 0.0f || this->bIsMoveDown || this->bIsMoveUp || this->bIsMoveLeft || this->bIsHiddenPlayerInItem)
		return;
	GetMesh()->SetRelativeRotation(this->RightMove);
	AddMovementInput(GetActorRightVector(), Amount);
}

void ABCGJamBaseCharacter::MoveDownPlayer(float Amount)
{
	this->bIsMoveDown = Amount < 0.0f;
	if (Amount == 0.0f || this->bIsMoveRight || this->bIsMoveUp || this->bIsMoveLeft || this->bIsHiddenPlayerInItem)
		return;
	GetMesh()->SetRelativeRotation(this->BackMove);
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ABCGJamBaseCharacter::MoveLeftPlayer(float Amount)
{
	this->bIsMoveLeft = Amount < 0.0f;
	if (Amount == 0.0f || this->bIsMoveRight || this->bIsMoveUp || this->bIsMoveDown || this->bIsHiddenPlayerInItem)
		return;
	GetMesh()->SetRelativeRotation(this->LeftMove);
	AddMovementInput(GetActorRightVector(), Amount);
}

