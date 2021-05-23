// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleA.h"

AModuleA::AModuleA()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> ModuleMeshFinder(TEXT("StaticMesh'/Game/Spacewalkers/Art/SM_ALetter.SM_ALetter'"));
	if(ModuleMeshFinder.Succeeded())
		ModuleMesh = ModuleMeshFinder.Object;
}

void AModuleA::BeginPlay()
{
	Super::BeginPlay();
}

void AModuleA::ModuleTick()
{
	Super::ModuleTick();
}
