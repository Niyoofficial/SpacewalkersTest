// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleA.h"

#include "GameBoard.h"

UModuleA::UModuleA()
{
	MaxLevel = 5;

	ConstructorHelpers::FObjectFinder<UStaticMesh> ModuleMeshFinder(TEXT("StaticMesh'/Game/Spacewalkers/Art/SM_ALetter.SM_ALetter'"));
	if(ModuleMeshFinder.Succeeded())
		ModuleMesh = ModuleMeshFinder.Object;
}

void UModuleA::ModuleTick()
{
	Super::ModuleTick();

	GameBoard.Get()->ModifyResource(ResourceGenerated);
	
	OnPopUp.Broadcast(MODULE_TEXT_FORMAT("Plus {0}", ResourceGenerated), FLinearColor::Green);
}

void UModuleA::OnLevelUp()
{
	Super::OnLevelUp();

	ResourceGenerated += 10;
}
