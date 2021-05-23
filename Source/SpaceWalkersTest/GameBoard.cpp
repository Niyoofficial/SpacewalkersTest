// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBoard.h"

#include "ModuleA.h"

AGameBoard::AGameBoard()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();

	//Initialize the whole array so we can easily check for nullptr later
	Board.AddDefaulted(5);
	for(auto& by : Board)
		by.AddZeroed(5);
}

void AGameBoard::AddModule(AModuleBase* Module, int32 X, int32 Y)
{
	if(!Board[X][Y])
	{
		Board[X][Y] = Module;
	}
}
