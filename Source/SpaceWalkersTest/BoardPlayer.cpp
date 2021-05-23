// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPlayer.h"

ABoardPlayer::ABoardPlayer()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABoardPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

