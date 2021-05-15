// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Public/AI/BCGJamAITargetPoint.h"

void ABCGJamAITargetPoint::BeginPlay()
{
	Super::BeginPlay();
	this->LocationTargetPoint = GetActorLocation();
}
