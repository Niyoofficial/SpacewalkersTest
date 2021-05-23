// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleBase.h"

AModuleBase::AModuleBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AModuleBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &AModuleBase::ModuleManager, TickDelay);
}

void AModuleBase::ModuleManager()
{
	ModuleTick();

	GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &AModuleBase::ModuleManager, TickDelay);
}

void AModuleBase::ModuleTick()
{
}

void AModuleBase::Test()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("ModuleTest!"));
}
